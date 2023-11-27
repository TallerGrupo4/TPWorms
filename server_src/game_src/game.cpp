#include "game.h"
#include <chrono>
#include "../../common_src/yamlReader.h"
#include "../../common_src/constants.h"
#include "game_constants.h"
#include <iostream>

// #include "weapons.h"


Game::Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), listener(projectiles) , filter(), current_turn_player_id(INITIAL_WORMS_TURN), turn_time(TURN_TIME), team_turn(0), turn_cleaning(false) {
    world.SetContactListener(&listener);
    world.SetContactFilter(&filter);
}

Snapshot Game::start_and_send(Map& map, int number_of_players, std::map<char, std::vector<char>>& match_teams) {
    Snapshot snapshot = map.get_snapshot();
    builder.create_map(snapshot);
    water_level = map.water_level;

    // Assign teams
    std::vector <WormSnapshot> wormsSnapshots;
    // We should assign worms to each team (client) until there is no more worms to assign.
    // Now we are assigning all the amount_of_worms to each team (client).
    spawn_points = map.spawn_points;
    std::vector<b2Vec2> current_spawn_points = map.spawn_points;
    int current_id = 0;
    int amount_of_worms_per_team = std::floor(map.amount_of_worms / number_of_players);
    int remainder = map.amount_of_worms % number_of_players;
    for (int team_id = 0; team_id < number_of_players; team_id++) {
        for (int i = 0; i < amount_of_worms_per_team; i++) {
            add_player(current_id, team_id, current_spawn_points);
            wormsSnapshots.push_back(teams[team_id].get_worm(current_id)->get_snapshot());
            // teams[team_id].push_back(players[current_id]);
            match_teams[team_id].push_back(current_id);
            current_id++;
        }
    }
    for (int i = 0; i < remainder; i++) {
        add_player(current_id, i, current_spawn_points);
        wormsSnapshots.push_back(teams[i].get_worm(current_id)->get_snapshot());
        // teams[i].push_back(players[current_id]);
        match_teams[i].push_back(current_id);
        current_id++;
    }
    int amount_of_teams_with_less_worms = number_of_players - remainder;
    if (amount_of_teams_with_less_worms != number_of_players) {
        for (int i = 0; i < amount_of_teams_with_less_worms; i++) {
            std::cout << "Add health to team: " << remainder + i << std::endl;
            // add_health_to_team(teams[remainder + i]);
        }
    }
    current_turn_player_id = teams[0].get_next_player_id();
    snapshot.worms = wormsSnapshots;
    return snapshot;
}

void Game::add_player(int current_id, int team_id , std::vector<b2Vec2>& spawn_points) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
    int rand = std::rand() % spawn_points.size();
    b2Vec2 spawn_point = spawn_points[rand];
    b2Body* player = builder.create_worm(spawn_point.x , spawn_point.y);
    teams[team_id].push_back(std::make_shared<Worm>(player, current_id, team_id));
    spawn_points.erase(spawn_points.begin() + rand);
}

void Game::move_player(int id, int direction) {
    try {
        if (current_turn_player_id != id || turn_cleaning) return;

        std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
        worm->move(direction);
    } catch (const std::exception& err) {
        std::cerr << "id is: " << id << std::endl;
        std::cerr << "move_player failed with: " << err.what() << "\n";
    }
}

void Game::jump_player(int id , int direction){
    try {
        if (current_turn_player_id != id || turn_cleaning) return;
        std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
        worm->jump(direction);
    }   catch (const std::exception& err) {
        std::cerr << "jump_player failed with: " << err.what() << "\n";
    }
}

void Game::player_use_tool(int id, int potency, float pos_x , float pos_y) {
    if (current_turn_player_id != id || turn_cleaning) return;
    std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
    worm->use_tool(potency, pos_x, pos_y, projectiles);
    turn_time = 3 * FPS;
}

void Game::player_aim(int id, int increment, int direction) {
    if (current_turn_player_id != id || turn_cleaning) return;
    std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
    worm->aim(increment, direction);
}

void Game::player_change_tool(int id, int direction) {
    if (current_turn_player_id != id || turn_cleaning) return;
    std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
    worm->change_tool(direction);
}

void Game::remove_player(char army_id){
    //TODO: Remove all players from that army
    return ;
}

void Game::check_angles(Worm& w){
    if (w.get_state() == STILL){
        if (abs ( w.get_angle() ) <= LAST_ANG_THRESHOLD){
            w.set_last_still_angle(w.body->GetAngle());
        }
    }
    if (abs (w.get_angle()) >= ANG_THRESHOLD){
        b2Body* body = w.body;
        body->SetTransform(body->GetPosition(), w.last_angle());
    }
}


void Game::check_states(Worm& w){
    if (w.get_state() == SHOOTED || w.get_state() == AIMING) {return;}
    if (w.get_state() == DAMAGED){
        if (current_turn_player_id == w.get_id()) {
            turn_time = 0;
            return;
        }
    }
    if (w.body->GetPosition().y <= water_level){
        w.set_state(DEAD);
        if (current_turn_player_id == w.get_id()){
            turn_time = 0;
        }
        return;
    }
    if (w.body->GetContactList()) {
        for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()){
            b2Body* body = w.body->GetContactList()->other;
            if (body && body->GetType() == b2_staticBody){
                if (body->GetFixtureList()->GetFriction() == 0){
                    w.set_state(SLIDING);
                }
            }
        }
    }
    float diff = w.body->GetPosition().y - w.get_last_y();
    if (diff < -1.5 && w.get_state() != FALLING && !w.in_contact() && w.body->GetLinearVelocity().Length() > 1){
        w.set_state(FALLING);
    }
    if (w.body->GetLinearVelocity() == b2Vec2_zero && w.body->GetAngularVelocity() == 0){
        w.set_state(STILL);
    }
}

void Game::check_velocities(Worm& w){
    if (w.body->GetLinearVelocity().Length() < VEL_THRESHOLD ){
        w.body->SetLinearVelocity(b2Vec2_zero);
        w.body->SetAngularVelocity(0);
    } 
    if (abs (w.body->GetAngularVelocity()) > 0){
        w.body->SetAngularVelocity(0);
    }

}

void Game::worm_comprobations(){
    for (auto& team: teams) {
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            if (worm->get_state() == DEAD){
                continue;
            }
            check_velocities(*worm);
            check_states(*worm);
            check_angles(*worm);
        }
    }
}

void Game::game_post_cleanup(){
    for (auto& projectile : projectiles){
        if (projectile->get_state() == EXPLODED){
            world.DestroyBody(projectile->get_body());
            projectiles.erase(projectile);
        }
    }

    for (auto& team: teams) {
        std::vector<char> dead_worms_ids;
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            if (worm->get_state() == DAMAGED || worm->get_state() == SHOOTED){
                worm->set_state(STILL);
            }
            if (worm->get_state() == DEAD && worm->body != nullptr) {
                world.DestroyBody(worm->body);
                worm->body = nullptr;
                dead_worms_ids.push_back(worm->get_id());
                std::cout << "Worm " << (int) worm->get_id() << " is dead" << std::endl;
                std::cout << "There are still " << team.second.size() - 1 << " worms alive" << std::endl;
            }
        }
        for (char id: dead_worms_ids) {
            team.second.remove_player(id);
        }
    }
    
}

void Game::projectiles_comprobations(int it){
for (auto& projectile : projectiles){
    if (projectile->get_state() == ALIVE){
        projectile->decresease_timer(it);
        if (projectile->get_timer() <= 0){
            projectile->explode(projectiles);
        }
    }
}
}

void Game::step(int it) {
    float time_simulate = (float) it / FPS;
    // reap_dead();
    world.Step(time_simulate, 8, 3);
    worm_comprobations();
    projectiles_comprobations(it);

    if (turn_time > 0){
        turn_time -= it;
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

    printf("turn time: %d\n", turn_time);
}

void Game::turn_clean_up(){
    printf("cleaning time: %d\n" , cleaning_time);
    for (auto& team: teams) {
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            // I think this if DEAD is not necessary anymore
            if (worm->get_state() == DEAD) {continue;}
            worm->set_used_tool(false);
            if (worm->body->GetLinearVelocity() != b2Vec2_zero || worm->body->GetAngularVelocity() != 0){
                cleaning_time = 1 * FPS;
                return;
            }
        }
        // std::shared_ptr<Worm> worm = pair.second;
        // if (worm->get_state () == DEAD) {continue;}
        // if (worm -> get_state() != STILL){
        //     return false;
        // }
    }
    // if (projectiles.size() != 0){ return NOT_DONE;}
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
        current_turn_player_id = teams[0].get_next_player_id();
        std::cout << "Current turn player id: " << current_turn_player_id << std::endl;
        turn_time = TURN_TIME;
        return;
    }
    // Switch to the next player's turn from another team
    std::cout << "turn_time " << turn_time << std::endl;
    bool worm_is_dead = false;
    do {
        team_turn++;
        if (team_turn > ((int) teams.size() - 1)) {
            // End of round
            std::cout << "End of round" << std::endl;
            team_turn = 0;
        }
        if (teams[team_turn].is_empty()) {
            std::cout << "Team " << team_turn << " is empty" << std::endl;
            continue;
        }
        current_turn_player_id = teams[team_turn].get_next_player_id();
        worm_is_dead = teams[team_turn].get_worm(current_turn_player_id)->get_state() == DEAD;
        std::cout << "Current turn player id: " << current_turn_player_id << std::endl;
        std::cout << "Team turn: " << team_turn << std::endl;
    } while (worm_is_dead);
    // Reset the turn timer for the next player
    turn_time = TURN_TIME;
}

Snapshot Game::get_game_snapshot() {
    std::vector<WormSnapshot> worms;
    for (auto& team: teams) {
        for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
            worms.push_back(worm->get_snapshot());
        }
        // worms.push_back(pair.second->get_snapshot());
    }
    std::vector<ProjectileSnapshot> projectiles_snaps;
    for (auto& projectile : projectiles){
        projectiles_snaps.push_back(projectile->get_snapshot());
    }
    Snapshot snapshot(worms, projectiles_snaps , {});
    snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
    return snapshot;
}

Game::~Game() {}

