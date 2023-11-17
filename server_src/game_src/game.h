#include <string>
#include <vector>

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
    std::vector<Worm> players;
    int turn;

public:
    Game(): world(b2Vec2(0.0f, -10.0f)), builder(world), turn(0) {}

    Snapshot start_and_send(Map& map, int number_of_players) {
        Snapshot snapshot({}, map.platforms);
        snapshot.set_dimensions(map.height, map.width);
        builder.create_map(snapshot);
        std::vector <WormSnapshot> wormsSnapshots;
        for (int i = 0; i < number_of_players; i++) {
            add_player(i);
            wormsSnapshots.push_back(players[i].get_snapshot());
        }
        std:: cout << (int) wormsSnapshots.size() << std::endl;
        snapshot.worms = wormsSnapshots;
        return snapshot;
    }

    void add_player(int current_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = builder.create_worm(0, 0);
        players.push_back(Worm(current_id, player));
    }

    void move_player(char id, int direction) {
        Worm player = players[id];
        player.move(direction);
    }

    void remove_player(char id){
        //TODO
        return ;
    }


// Check parameter..
    void step(int it) {
        float time_simulate = (float) it / FPS;
        world.Step(time_simulate, 8, 3);
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

    Snapshot get_game_snapshot() {
        std::vector<WormSnapshot> worms;
        for (Worm& worm: players) {
            worms.push_back(worm.get_snapshot());
        }
        Snapshot snapshot(worms, {});
        return snapshot;
    }
};

#endif  // GAME_H