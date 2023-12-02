#include "game.h"
#include <chrono>
#include "../../common_src/yamlReader.h"
#include "../../common_src/constants.h"
#include "../../common_src/custom_errors.h"
#include "game_constants.h"
#include <iostream>

// #include "weapons.h"

#define EXTRA_HEALTH ConfigSingleton::getInstance().get_extra_health()

Game::Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), listener() , filter(), projectile_manager(), worm_comprobator(), current_turn_player_id(INITIAL_WORMS_TURN), turn_time(TURN_TIME), team_turn(0), turn_cleaning(false), game_ended(false), winner_team_id(-1) {
    world.SetContactListener(&listener);
    world.SetContactFilter(&filter);
}

Snapshot Game::start_and_send(Map& map, int number_of_players, std::map<char, std::vector<char>>& match_teams) {
    Snapshot snapshot = map.get_snapshot();
    builder.create_map(snapshot);
    water_level = map.water_level;
    spawn_points = map.spawn_points;
    height = map.height;
    width = map.width;

    std::vector<b2Vec2> current_spawn_points = map.spawn_points;
    std::vector<WormSnapshot> worm_snaps =  assign_worms_to_teams(map, current_spawn_points, match_teams , number_of_players);

    current_turn_player_id = teams[0].get_next_player_id();

    snapshot.worms = worm_snaps;
    return snapshot;
}

std::vector<WormSnapshot> Game::assign_worms_to_teams(Map& map, std::vector<b2Vec2>& current_spawn_points, std::map<char, std::vector<char>>& match_teams, int number_of_players) {
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
    if (remainder <= 0) return wormsSnapshots;
    for ( int i = 0 ; i < number_of_players; i++) {
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


void Game::add_player(int current_id, int team_id , std::vector<b2Vec2>& spawn_points) { 
    int rand = std::rand() % spawn_points.size();
    b2Vec2 spawn_point = spawn_points[rand];
    b2Body* player = builder.create_worm(spawn_point.x , spawn_point.y);
    teams[team_id].push_back(std::make_shared<Worm>(player, current_id, team_id));
    spawn_points.erase(spawn_points.begin() + rand);
}

std::shared_ptr<Worm> Game::get_worm_if_can_act(int id){
    if (current_turn_player_id != id || turn_cleaning){return nullptr;}
    std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
    return worm;
}

void Game::move_player(int id, int direction) {
        if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)){
            worm->move(direction);
        }
}

void Game::jump_player(int id , int direction){
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)){
        worm->jump(direction);
    }
}

void Game::player_use_tool(int id, int potency, float pos_x , float pos_y, int timer) {
    if (std::shared_ptr<Worm> worm = get_worm_if_can_act(id)) {
        if (worm->use_tool(potency, pos_x, pos_y, timer, projectile_manager)){
        turn_time = 3 * FPS;
        }
    }
}

void Game::player_aim(int id, int increment, int direction) {
    if ( std::shared_ptr<Worm> worm = get_worm_if_can_act(id)){
        worm->aim(increment, direction);
    }
}

void Game::player_change_tool(int id, int direction) {
    if ( std::shared_ptr<Worm> worm = get_worm_if_can_act(id)){
        worm->change_tool(direction);
    }
}


void Game::remove_army(char army_id){
    for (auto& team: teams) {
        if (team.first == army_id){
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                worm->set_state(DEAD);
            }
            return;
        }
    }
}


void Game::worm_comprobations(){
    for (auto& team: teams) {
        worm_comprobator.check_during_game(team.second.get_worms(), turn_time, current_turn_player_id, height , width, water_level);
    }
}

void Game::game_post_cleanup(){
    projectile_manager.update_post_game(world);
    box_manager.reap_boxes(world);

    for (auto& team: teams) {
        std::list<char> dead_worms_ids = worm_comprobator.check_post_turn(team.second.get_worms(), world);
        for (char id: dead_worms_ids) {
            team.second.remove_player(id);
        }
    }
}

void Game::step(int it) {
    float time_simulate = (float) it / FPS;
    world.Step(time_simulate, 8, 3);

    worm_comprobations();
    projectile_manager.update_during_game(it , width , height);

    if (turn_time > 0){
        turn_time -= it;
        if (teams[team_turn].get_worm(current_turn_player_id)->get_state() == DEAD){
            manage_turn();
        }
    } else {
        if (!turn_cleaning ){
            cleaning_time = 1 * FPS;
        }
        turn_cleaning = true;
        turn_clean_up();
        if (!turn_cleaning){
            manage_turn();
        }
    }
}

bool Game::check_end_game() {
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

void Game::turn_clean_up(){
    for (auto& team: teams) {
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            // I think this if DEAD is not necessary anymore
            if (worm->get_state() == DEAD) {continue;}
            worm->set_used_tool(false);
            if (worm->state == AIMING) {
                worm->set_state(STILL);
            }
            worm->store_tool();
            if (worm->body->GetLinearVelocity() != b2Vec2_zero || worm->body->GetAngularVelocity() != 0){
                cleaning_time = 1 * FPS;
                return;
            }
        }
    }

    if (projectile_manager.has_projectiles()){
        cleaning_time = 1 * FPS;
        return;
    }
    
    if (cleaning_time > 0){
        cleaning_time--;
    } else {
        turn_cleaning = false;
    }
}

void Game::manage_turn() {
    // Perform any necessary actions at the end of the turn
    // For example, switch to the next player's turn, reset the timer, etc.

    // Check if the turn time is over
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
        if (team_turn > ((int) teams.size() - 1)) {
            // End of round
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
    // Reset the turn timer for the next player
    turn_time = TURN_TIME;
    projectile_manager.reset_id();
    spawn_provision_box();
}

void Game::spawn_provision_box(){
    std::vector<b2Vec2> current_spawn_points = spawn_points;
    while (current_spawn_points.size() > 0){
        int rand = std::rand() % current_spawn_points.size();
        b2Vec2 spawn_point = current_spawn_points[rand];
        if (box_manager.position_is_free(spawn_point, world)){
            box_manager.add_box(builder.create_provision_box_body(spawn_point.x, spawn_point.y));
            return;
        }
        current_spawn_points.erase(current_spawn_points.begin() + rand);
    }
}

Snapshot Game::get_end_game_snapshot() {
    std::vector<WormSnapshot> worms;
    for (auto& team: teams) {
        if (team.first != winner_team_id) continue;
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            worm->state = WINNER;
            worms.push_back(worm->get_snapshot());
        }
    }
    Snapshot snapshot(worms, {} , {}, {});
    snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
    snapshot.set_end_game();
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
    std::vector<ProjectileSnapshot> projectiles_snaps = projectile_manager.get_projectiles_snapshot();
    std::vector<ProvisionBoxSnapshot> boxes_snaps = box_manager.get_boxes_snapshot();
    Snapshot snapshot(worms, projectiles_snaps , {}, boxes_snaps);
    snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
    snapshot.set_armies_health(teams_health);
    return snapshot;
}

Game::~Game() {}

