#include "game.h"

#include <chrono>
#include <iostream>
#include <list>

#include "../../common_src/constants.h"
#include "../../common_src/custom_errors.h"
#include "../../common_src/yamlReader.h"

#include "game_constants.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Game::Game():
        water_level(0),
        world(b2Vec2(0.0f, -10.0f)),
        height(0),
        width(0),
        builder(world),
        listener(),
        filter(),
        projectile_manager(),
        worm_comprobator(),
        current_turn_player_id(INITIAL_WORMS_TURN),
        shoot_cheat(false),
        turn_time(TURN_TIME),
        team_turn(0),
        turn_cleaning(false),
        cleaning_time(0),
        game_ended(false),
        winner_team_id(-1) {
    world.SetContactListener(&listener);
    world.SetContactFilter(&filter);
}

Snapshot Game::start_and_send(const Map& map, int number_of_players,
                              std::map<char, std::vector<char>>& match_teams) {
    // First it reads the mapa from the chosen map
    Snapshot snapshot = map.get_snapshot();
    builder.create_map(snapshot);
    water_level = map.water_level;
    spawn_points = map.spawn_points;
    height = map.height;
    width = map.width;

    // then it assigns the worms to the teams it received, saving that information in match_teams
    // so it can then send it to the client.
    std::vector<b2Vec2> current_spawn_points = map.spawn_points;
    std::vector<WormSnapshot> worm_snaps =
            assign_worms_to_teams(map, current_spawn_points, match_teams, number_of_players);

    // Finally it prepares the game for the first turn and send the snapshot with the map to the
    // clients
    current_turn_player_id = teams[0].get_next_player_id();
    projectile_manager.randomize_wind();
    snapshot.set_wind_force(projectile_manager.get_wind_force());
    snapshot.worms = worm_snaps;
    return snapshot;
}

std::vector<WormSnapshot> Game::assign_worms_to_teams(
        // This method distributes the worm in an equal way to all the teams, and if there are more
        // worms than teams, it add more life to the teams with less worms.
        const Map& map, std::vector<b2Vec2>& current_spawn_points,
        std::map<char, std::vector<char>>& match_teams, int number_of_players) {
    std::vector<WormSnapshot> wormsSnapshots;
    int current_id = 0;

    int amount_of_worms_per_team = std::floor(map.amount_of_worms / number_of_players);
    int remainder = map.amount_of_worms % number_of_players;

    for (int team_id = 0; team_id < number_of_players; team_id++) {
        for (int i = 0; i < amount_of_worms_per_team; i++) {
            add_player(current_id, team_id, current_spawn_points);
            wormsSnapshots.push_back(teams[team_id].get_worm(current_id)->get_snapshot());
            match_teams[team_id].push_back(current_id);
            current_id++;
        }
    }
    if (remainder <= 0)
        return wormsSnapshots;
    for (int i = 0; i < number_of_players; i++) {
        if (i >= remainder) {
            teams[i].add_health_to_worms(EXTRA_HEALTH);
        } else {
            add_player(current_id, i, current_spawn_points);
            wormsSnapshots.push_back(teams[i].get_worm(current_id)->get_snapshot());
            match_teams[i].push_back(current_id);
            current_id++;
        }
    }
    return wormsSnapshots;
}


void Game::add_player(int current_id, int team_id, std::vector<b2Vec2>& spawn_points) {
    // This method simply adds the worm to the team and randomizes it's spawn
    int rand = std::rand() % spawn_points.size();
    b2Vec2 spawn_point = spawn_points[rand];
    b2Body* player = builder.create_worm(spawn_point.x, spawn_point.y);
    teams[team_id].push_back(std::make_shared<Worm>(player, current_id, team_id));
    spawn_points.erase(spawn_points.begin() + rand);
}

std::shared_ptr<Worm> Game::get_worm_if_can_act(int id) {
    if (current_turn_player_id != id || turn_cleaning) {
        return nullptr;
    }
    std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
    return worm;
}

void Game::move_player(int id, int direction) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        worm->move(direction);
    }
}

void Game::jump_player(int id, int direction) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        worm->jump(direction);
    }
}

void Game::player_use_tool(int id, int potency, float pos_x, float pos_y, int timer) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        if (worm->use_tool(potency, pos_x, pos_y, timer, projectile_manager)) {
            if (shoot_cheat) {
                worm->has_used_tool = false;
            } else {
                turn_time = 3 * FPS;
            }
        }
    }
}

void Game::player_aim(int id, int increment, int direction) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        worm->aim(increment, direction);
    }
}

void Game::player_change_tool(int id, int direction) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        worm->change_tool(direction);
    }
}


void Game::remove_army(char army_id) {
    auto teamIt = std::find_if(teams.begin(), teams.end(),
                               [army_id](const auto& team) { return team.first == army_id; });

    if (teamIt != teams.end()) {
        // Found the team with the specified army_id
        for (std::shared_ptr<Worm> worm: teamIt->second.get_worms()) {
            worm->set_state(DEAD);
        }
    }
}


void Game::worm_comprobations() {
    for (auto& team: teams) {
        worm_comprobator.check_during_game(team.second.get_worms(), turn_time,
                                           current_turn_player_id, height, width, water_level);
    }
}

void Game::game_post_cleanup() {
    projectile_manager.update_post_game(world);
    box_manager.reap_boxes(world);

    for (auto& team: teams) {
        std::list<char> dead_worms_ids =
                worm_comprobator.check_post_game(team.second.get_worms(), world);
        for (char id: dead_worms_ids) {
            team.second.remove_player(id);
        }
    }
}


void Game::step(int it) {
    float time_simulate = (float)it / FPS;
    // Step the physics simulation
    world.Step(time_simulate, 8, 3);

    // Update the projectiles and worms during the game
    projectile_manager.update_during_game(it, width, height, water_level);
    worm_comprobations();

    // Here it checks if the turn has ended, if it has ended it will start cleaning.
    // When it finishes cleaning the current turn, it will start the next turn
    if (turn_time > 0) {
        turn_time -= it;
        // Here we check if the current worm has died, if it has, we start cleaning
        if (teams[team_turn].get_worm(current_turn_player_id)->get_state() == DEAD) {
            turn_time = 0;
            turn_cleaning = true;
            cleaning_time = 1 * FPS;
            turn_clean_up();
        }
    } else {
        if (!turn_cleaning) {
            cleaning_time = 1 * FPS;
        }
        turn_cleaning = true;
        turn_clean_up();
        if (!turn_cleaning) {
            manage_turn();
        }
    }
}

bool Game::check_end_game() {
    // This method checks if the game has ended, if it has, it will set the winner_team_id
    // This is used so the client can know if the game has ended and render properly
    bool no_worms_left = true;
    int alive_teams = 0;
    for (auto& team: teams) {
        if (team.second.size() > 0) {
            no_worms_left = false;
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                if (worm->get_state() != DEAD) {
                    alive_teams++;
                    winner_team_id = team.first;
                    break;
                }
            }
        }
    }
    if (no_worms_left || alive_teams == 1) {
        game_ended = true;
    }
    return game_ended;
}

void Game::turn_clean_up() {
    for (auto& team: teams) {
        if (!worm_comprobator.have_worm_finished_turn(team.second.get_worms(), cleaning_time)) {
            return;
        }
    }

    if (projectile_manager.has_projectiles()) {
        cleaning_time = 1 * FPS;
        return;
    }

    if (cleaning_time > 0) {
        cleaning_time--;
    } else {
        turn_cleaning = false;
    }
}

void Game::manage_turn() {
    if (teams.size() == 1) {
        try {
            current_turn_player_id = teams[0].get_next_player_id();
        } catch (const NoWormsLeft& err) {
            std::cerr << err.what() << std::endl;
            // End of the game
        }
        turn_time = TURN_TIME;
        return;
    }
    // Switch to the next player's turn from another team
    bool worm_is_dead = false;
    do {
        team_turn++;
        if (team_turn > ((int)teams.size() - 1)) {
            // End of round
            projectile_manager.randomize_wind();

            team_turn = 0;
        }
        try {
            current_turn_player_id = teams[team_turn].get_next_player_id();
        } catch (const NoWormsLeft& err) {
            std::cout << err.what() << std::endl;
            worm_is_dead = true;
            continue;
        }
        worm_is_dead = teams[team_turn].get_worm(current_turn_player_id)->get_state() == DEAD;
    } while (worm_is_dead);
    // Resets the information of the current turn + adds a new provision box
    turn_time = TURN_TIME;
    shoot_cheat = false;
    projectile_manager.reset_id();
    spawn_provision_box();
}

void Game::spawn_provision_box() {
    std::vector<b2Vec2> current_spawn_points = spawn_points;
    while (current_spawn_points.size() > 0) {
        int rand = std::rand() % current_spawn_points.size();
        b2Vec2 spawn_point = current_spawn_points[rand];
        if (box_manager.position_is_free(spawn_point, world)) {
            box_manager.add_box(builder.create_provision_box_body(spawn_point.x, spawn_point.y));
            return;
        }
        current_spawn_points.erase(current_spawn_points.begin() + rand);
    }
}

void Game::toggle_shoot_cheat(char id) {
    if (!turn_cleaning) {
        shoot_cheat = !shoot_cheat;
        if (shoot_cheat) {
            if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
                worm->has_used_tool = false;
            }
        }
    }
}

void Game::cheat_turn_time() {
    if (!turn_cleaning) {
        turn_time += 10 * FPS;
    }
}

void Game::cheat_ammo(char id) {
    if (!turn_cleaning) {
        if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
            worm->cheat_ammo();
        }
    }
}

void Game::cheat_life(char id) {
    if (!turn_cleaning) {
        if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
            worm->add_health(100);
        }
    }
}

Snapshot Game::get_end_game_snapshot() {
    std::vector<WormSnapshot> worms;
    for (auto& team: teams) {
        if (team.first != winner_team_id)
            continue;
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            worm->state = WINNER;
            worms.push_back(worm->get_snapshot());
        }
    }
    Snapshot snapshot(worms, {}, {}, {});
    snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
    snapshot.set_end_game();
    snapshot.set_wind_force(projectile_manager.get_wind_force());
    return snapshot;
}

Snapshot Game::get_game_snapshot() {
    std::vector<WormSnapshot> worms;
    std::map<char, int> teams_health;
    for (auto& team: teams) {
        int team_health = 0;
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            worms.push_back(worm->get_snapshot());
            team_health += worm->life;
        }
        teams_health[team.first] = team_health;
    }
    std::vector<ProjectileSnapshot> projectiles_snaps =
            projectile_manager.get_projectiles_snapshot();
    std::vector<ProvisionBoxSnapshot> boxes_snaps = box_manager.get_boxes_snapshot();
    Snapshot snapshot(worms, projectiles_snaps, {}, boxes_snaps);
    snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
    snapshot.set_armies_health(teams_health);
    snapshot.set_wind_force(projectile_manager.get_wind_force());
    return snapshot;
}

Game::~Game() {}
