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
// #include "weapons.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

class Game {
    int water_level;
    b2World world;
    GameBuilder builder;
    MyListener listener;
    std::unordered_set<b2ContactListener*> listeners;
    std::unordered_map<char,std::shared_ptr<Worm>> players;
    // std::unordered_set<std::shared_ptr<Projectile>> projectiles;
    int current_turn_player_id;
    int turn_time;


public:
    Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), current_turn_player_id(INITIAL_WORMS_TURN), turn_time(TURN_TIME) {
        listener = MyListener();
        world.SetContactListener(&listener);
    }

    Snapshot start_and_send(Map& map, int number_of_players) {
        Snapshot snapshot({}, map.platforms);
        snapshot.set_dimensions(map.height, map.width);
        builder.create_map(snapshot);
        std::vector <WormSnapshot> wormsSnapshots;
        for (int i = 0; i < number_of_players; i++) {
            add_player(i);
            wormsSnapshots.push_back(players[i]->get_snapshot());
        }
        snapshot.worms = wormsSnapshots;
        return snapshot;
    }

    void add_player(int current_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = builder.create_worm(0, 5);
        players[current_id] = std::make_shared<Worm>(player, current_id);
    }

    void move_player(int id, int direction) {
        if (current_turn_player_id != id) return;
        std::shared_ptr<Worm> player = players.at(id);
        player->move(direction);
    }

    void jump_player(int id , int direction){
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

    void remove_player(char id){
        //TODO
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
            check_velocities(*worm);
            check_states(*worm);
            check_angles(*worm);
        }
    }


    void print_current_state(){
        std::shared_ptr<Worm> worm = players.at(current_turn_player_id);
        std::cout << "Worm " << current_turn_player_id << " state: " << worm->get_state() << std::endl;
    }

// Check parameter..
    void step(int it) {
        float time_simulate = (float) it / FPS;
        // reap_dead();
        worm_comprobations();
        print_current_state();

        world.Step(time_simulate, 8, 3);
        manage_turn(it);
        // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
        /*
        float time_simulate = (float) it / FPS;
        world.Step(1.0f / 60.0f, 8, 3);
        turn_manager.update(it);
        for (auto each_obj : obj) {
            // each_obj knows how to step
            each_obj->step(time_simulate);
        }
        */
        // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
    }

     void manage_turn(int it) {
        // Perform any necessary actions at the end of the turn
        // For example, switch to the next player's turn, reset the timer, etc.

        // Check if the turn time is over
        turn_time -= it;
        if (turn_time > 0) return;
        // Switch to the next player's turn
        current_turn_player_id = (current_turn_player_id + 1) % players.size();
        // Reset the turn timer for the next player
        turn_time = TURN_TIME;
    }

    Snapshot get_game_snapshot() {
        std::vector<WormSnapshot> worms;    
        for (auto& pair: players) { // Pair: {id, worm}
            worms.push_back(pair.second->get_snapshot());
        }
        Snapshot snapshot(worms, {});
        return snapshot;
    }

    ~Game(){
        for (auto listener : listeners){
            delete listener;
        }
    }
};

#endif  // GAME_H