#include <string>
#include <vector>

#include <algorithm>

#include <box2d/box2d.h>

#include "../../common_src/yamlReader.h"

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"
#include "../map.h"

#include "gamebuilder.h"
#include "worm.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

// (7.35235 , 2.253536) => *1000 (7352 , 2253) => (7352*60 , 2253*60) => (441120 , 135180) => (441120/1000 , 135180/1000) => (int(441.12) , int(135.18))

class Game {
    int water_level;
    b2World world;
    GameBuilder builder;
    std::vector<std::shared_ptr<Worm>>  players;
    int turn;

public:
    Game(): world(b2Vec2(0.0f, -10.0f)), builder(&world), turn(0) {}

    Snapshot start_and_send(Map& map, int number_of_players) {
        Snapshot snapshot({}, map.platforms);
        snapshot.set_dimensions(map.height, map.width);
        builder.create_map(snapshot);
        std::vector <WormSnapshot> wormsSnapshots;
        for (int i = 0; i < number_of_players; i++) {
            add_player(i);
            wormsSnapshots.push_back(players[i]->get_snapshot());
        }
        std:: cout << (int) wormsSnapshots.size() << std::endl;
        snapshot.worms = wormsSnapshots;
        return snapshot;
    }

    void add_player(int current_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        players.push_back(std::make_shared<Worm>(current_id, builder.create_worm(0, 40)));
    }

    void move_player(char id, int direction) {
        players[id]->move(direction);
    }


    void remove_player(char id) {
        // players.erase(std::remove_if(players.begin(), players.end(),
        //                 [id](const Worm& worm) { return worm.get_id() == id; }),
        //             players.end());
    }

    // void remove_player(char id){
    //     //TODO
    //     // Something like this...
    //     players.erase(players.begin() + id);
    //     // players.erase(std::remove(players.begin(), players.end(), id), players.end());
    //     return ;
    // }


// Check parameter..
    void step(int it) {
        float time_simulate = it * (FRAME_TIME);
        world.Step( time_simulate, 8, 3);
        //Iterate bodies in world 
        // for (b2Body* body = world.GetBodyList(); body != nullptr; body = body->GetNext()) {
        //     //Get position and angle of body
        //     float x = body->GetPosition().x;
        //     float y = body->GetPosition().y;
        //     if (body->GetType() == b2_dynamicBody){
        //         std::cout << "pos de worm x: " << int(x) << std::endl;
        //         std::cout << "pos del worm y: " << y << std::endl;
        //     } else{
        //         std::cout << "pos de plataforma x: " << int(x) << std::endl;
        //         std::cout << "pos del plataforma y: " << y << std::endl;
        //     }
        for (auto each_player : players) {
            if (each_player->body->GetLinearVelocity() == b2Vec2(0, 0)){
               each_player->state = STILL;
            }
        }
    }
        // std::shared_ptr<Worm> w = players[0];
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
    

    Snapshot get_game_snapshot() {
        std::vector<WormSnapshot> worms;
        for (std::shared_ptr<Worm> worm: players) {
            worms.push_back(worm->get_snapshot());
        }
        Snapshot snapshot(worms, {});
        return snapshot;
    }
};

#endif  // GAME_H