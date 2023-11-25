#include <chrono>
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
    int water_level;
    b2World world;
    GameBuilder builder;
    MyListener listener;
    MyFilter filter;
    std::unordered_map<char,std::shared_ptr<Worm>> players;
    std::map<uint8_t, Team> teams;
    // std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    int current_turn_player_id;
    int turn_time;
    int team_turn;



public:
    Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), current_turn_player_id(INITIAL_WORMS_TURN), turn_time(TURN_TIME), team_turn(0) {
        listener = MyListener();
        filter = MyFilter();
        world.SetContactListener(&listener);
        world.SetContactFilter(&filter);
    }

    Snapshot start_and_send(Map& map, int number_of_players, std::map<char, std::vector<char>>& match_teams) {
        Snapshot snapshot({}, map.platforms);
        snapshot.set_dimensions(map.height, map.width, WORM_WIDTH, WORM_HEIGHT, map.amount_of_worms);
        builder.create_map(snapshot);
        std::vector <WormSnapshot> wormsSnapshots;
        int current_id = 0;
        int amount_of_worms_per_team = map.amount_of_worms / number_of_players;
        int remainder = map.amount_of_worms % number_of_players;
        int got_remainder = remainder ? 1 : 0;
        for (int team_id = 0; team_id < number_of_players; team_id++) {
            if (team_id == number_of_players - 1) got_remainder = 0;
            for (int i = 0; i < amount_of_worms_per_team + got_remainder; i++) {
                add_player(current_id, team_id);
                wormsSnapshots.push_back(players[current_id]->get_snapshot());
                teams[team_id].push_back(current_id);
                match_teams[team_id].push_back(current_id);
                current_id++;
            }
        }
        int amount_of_teams_with_less_worms = number_of_players - remainder;
        if (amount_of_teams_with_less_worms != number_of_players) {
            for (int i = 0; i < amount_of_teams_with_less_worms; i++) {
                std::cout << "Add health to team: " << remainder + i << std::endl;
                // add_health_to_team(teams[remainder + i]);
            }
        }
        current_turn_player_id = teams[0].get_next_player();
        snapshot.worms = wormsSnapshots;
        return snapshot;
    }

    void add_player(int current_id, int team_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = builder.create_worm(0, -5);
        players[current_id] = std::make_shared<Worm>(player, current_id, team_id);
    }

    void move_player(int id, int direction) {
        std::cout << "Player trying to move: " << id << std::endl;
        std::cout << "Player turn: " << current_turn_player_id << std::endl;
        if (current_turn_player_id != id) return;
        std::shared_ptr<Worm> player = players.at(id);
        player->move(direction);
    }

    void jump_player(int id , int direction){
        if (current_turn_player_id != id) return;
        std::shared_ptr<Worm> player = players.at(id);
        player->jump(direction);
    }

    // void shoot_player(int id , int angle , int potency , std::shared_ptr<Weapon> weapon){
    //     std::shared_ptr<Worm> player = players.at(id);
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
            turn_time = 0;
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
        for (auto& pair: players) { // Pair: {id, worm}
            std::shared_ptr<Worm> worm = pair.second;
            if (worm->get_state() == DEAD){
                continue;
            }
            check_velocities(*worm);
            check_states(*worm);
            check_angles(*worm);
        }
    }


    void print_current_state(){
        std::shared_ptr<Worm> worm = players.at(current_turn_player_id);
        // std::cout << "Worm " << current_turn_player_id << " state: " << worm->get_state() << std::endl;
    }

    void worm_clean_up(){
        for (auto& pair: players) { // Pair: {id, worm}
            std::shared_ptr<Worm> worm = pair.second;
            if (worm->get_state() == DAMAGED){
                worm->set_state(STILL);
            }
            if (worm->get_state() == DEAD && worm->body != nullptr){
                world.DestroyBody(worm->body);
                worm->body = nullptr;
            }
        }
    }

// Check parameter..
    void step(int it) {
        float time_simulate = (float) it / FPS;
        // reap_dead();
        worm_comprobations();

        world.Step(time_simulate, 8, 3);

        manage_turn(it);
    }

    void manage_turn(int it) {
        // Perform any necessary actions at the end of the turn
        // For example, switch to the next player's turn, reset the timer, etc.

        // Check if the turn time is over
        turn_time -= it;
        if (turn_time > 0 || players.size() == 1) return;
            // Switch to the next player's turn from another team
        do {
            while (teams[++team_turn].finished_turn()) {
                team_turn++;
                if (team_turn > ((int) teams.size() - 1)) team_turn = -1;
                bool all_finished = true;
                for (auto& team: teams) {
                    if (!team.second.finished_turn()) {
                        all_finished = false;
                    }
                }
                if (all_finished) {
                    for (auto& team: teams) {
                        team.second.reset();
                    }
                    team_turn = 0;
                    std::cout << "Reset Team turn: " << team_turn << std::endl;
                    break;
                }
            }
            current_turn_player_id = teams[team_turn].get_next_player();
            if (team_turn == ((int) teams.size() - 1)) team_turn = -1;
            std::cout << "Current turn player id: " << current_turn_player_id << std::endl;
            std::cout << "Team turn: " << team_turn << std::endl;
        } while (players[current_turn_player_id]->get_state() == DEAD);
        // Reset the turn timer for the next player
        turn_time = TURN_TIME;
    }

    Snapshot get_game_snapshot() {
        std::vector<WormSnapshot> worms;    
        for (auto& pair: players) { // Pair: {id, worm}
            worms.push_back(pair.second->get_snapshot());
        }
        Snapshot snapshot(worms, {});
        snapshot.set_turn_time_and_worm_turn(turn_time, current_turn_player_id);
        return snapshot;
    }

    ~Game(){}
};

#endif  // GAME_H