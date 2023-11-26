#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <box2d/box2d.h>

#include "../../common_src/yamlReader.h"

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"
#include "../map.h"
#include "game_constants.h"
#include "gamebuilder.h"
#include "worm.h"
#include "listeners.h"
#include "filter.h"
#include "team.h"
// #include "weapons.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

class Game {
    float water_level;
    b2World world;
    GameBuilder builder;
    MyListener listener;
    MyFilter filter;
    std::vector<b2Vec2> spawn_points;
    std::map<uint8_t, Team> teams;
    // std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    int current_turn_player_id;
    int turn_time;
    int team_turn;



public:
    Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), listener() , filter(), current_turn_player_id(INITIAL_WORMS_TURN), turn_time(TURN_TIME), team_turn(0) {
        world.SetContactListener(&listener);
        world.SetContactFilter(&filter);
    }


    Snapshot start_and_send(Map& map, int number_of_players, std::map<char, std::vector<char>>& match_teams) {
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


    void add_player(int current_id, int team_id , std::vector<b2Vec2>& spawn_points) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        int rand = std::rand() % spawn_points.size();
        b2Vec2 spawn_point = spawn_points[rand];
        b2Body* player = builder.create_worm(spawn_point.x , spawn_point.y);
        teams[team_id].push_back(std::make_shared<Worm>(player, current_id, team_id));
        spawn_points.erase(spawn_points.begin() + rand);
    }

    void move_player(int id, int direction) {
        try {
            if (current_turn_player_id != id) return;

            std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
            worm->move(direction);
        } catch (const std::exception& err) {
            std::cerr << "id is: " << id << std::endl;
            std::cerr << "move_player failed with: " << err.what() << "\n";
        }
    }

    void jump_player(int id , int direction){
        try {
            if (current_turn_player_id != id) return;
            std::shared_ptr<Worm> worm = teams[team_turn].get_worm(id);
            worm->jump(direction);
        }   catch (const std::exception& err) {
            std::cerr << "jump_player failed with: " << err.what() << "\n";
        }
    }

    // void shoot_player(int id , int angle , int potency , std::shared_ptr<Weapon> weapon){
    //     std::shared_ptr<Worm> player = teams[team_turn].get_worm(id);
    //     b2Body* body = player->body;
    //     Projectile* projectile = weapon->create_projectile(body , angle, builder);
    //     projectiles.insert(std::shared_ptr<Projectile>(projectile));
    //     weapon->shoot(projectile , angle , potency);
    // }

    void remove_player(char army_id){
        //TODO: Remove all players from that army
        return ;
    }

    // void reap_dead(){
    //     for (auto& projectile : projectiles){
    //         if (!projectile->data.alive){
    //             world.DestroyBody(projectile->body);
    //             projectiles.erase(projectile);
    //         }
    //     }
    // }

    void check_angles(Worm& w){
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



    void check_states(Worm& w){
        if (w.get_state() == DAMAGED){
            if (teams[team_turn].get_worm(current_turn_player_id).get() == &w) {
                turn_time = 0;
                return;
            }
        }
        if (w.body->GetPosition().y <= water_level){
            w.set_state(DEAD);
            if (teams[team_turn].get_worm(current_turn_player_id).get() == &w){
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
        float diff = w.body->GetPosition().y - w.data.get_last_y();
        if (diff < -1.5 && w.get_state() != FALLING && !w.in_contact() && w.body->GetLinearVelocity().Length() > 1){
            w.set_state(FALLING);
        }
        if (w.body->GetLinearVelocity() == b2Vec2_zero && w.body->GetAngularVelocity() == 0){
            w.set_state(STILL);
        }
    }

    void check_velocities(Worm& w){
        if (w.body->GetLinearVelocity().Length() < VEL_THRESHOLD ){
            w.body->SetLinearVelocity(b2Vec2_zero);
            w.body->SetAngularVelocity(0);
        } 
        if (abs (w.body->GetAngularVelocity()) > 0){
            w.body->SetAngularVelocity(0);
        }

    }

    void worm_comprobations(){
        for (auto& team: teams) {
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                if (worm->get_state() == DEAD){
                    continue;
                }
                check_velocities(*worm);
                check_states(*worm);
                check_angles(*worm);
            }
            // std::shared_ptr<Worm> worm = pair.second;
            // if (worm->get_state() == DEAD){
            //     continue;
            // }
            // check_velocities(*worm);
            // check_states(*worm);
            // check_angles(*worm);
        }
    }


    void print_current_state(){
        // std::shared_ptr<Worm> worm = teams[team_turn].get_worm(current_turn_player_id);
        // std::cout << "Worm " << current_turn_player_id << " state: " << worm->get_state() << std::endl;
    }

    void worm_clean_up(){
        for (auto& team: teams) {
            std::vector<char> dead_worms_ids;
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                if (worm->get_state() == DAMAGED){
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
        if (turn_time <= 0 && turn_clean_up() == true){
                manage_turn();
        }
    }



// Check parameter..
    void step(int it) {
        float time_simulate = (float) it / FPS;
        // reap_dead();
        world.Step(time_simulate, 8, 3);

        worm_comprobations();


        turn_time -= it;
    }


    bool turn_clean_up(){
        for (auto& team: teams) {
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                // I think this if DEAD is not necessary anymore
                if (worm->get_state() == DEAD) {continue;}
                if (worm ->get_state() != STILL){
                    return false;
                }
            }
            // std::shared_ptr<Worm> worm = pair.second;
            // if (worm->get_state () == DEAD) {continue;}
            // if (worm -> get_state() != STILL){
            //     return false;
            // }
        }
        // if (projectiles.size() != 0){ return NOT_DONE;}
        return true;
    }

    void manage_turn() {
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

    Snapshot get_game_snapshot() {
        std::vector<WormSnapshot> worms;
        for (auto& team: teams) {
            for (std::shared_ptr<Worm> worm: team.second.get_worms()) {
                worms.push_back(worm->get_snapshot());
            }
            // worms.push_back(pair.second->get_snapshot());
        }
        Snapshot snapshot(worms, {});
        snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
        return snapshot;
    }

    ~Game(){}
};

#endif  // GAME_H