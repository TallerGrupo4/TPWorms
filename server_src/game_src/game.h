#include <string>
#include <vector>

#include <box2d/box2d.h>

#include "../../common_src/yamlReader.h"

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"

#include "gamebuilder.h"
#include "worm.h"

#ifndef GAME_H
#define GAME_H


class Game {
    // Debatible de tener el reader o no , taria bueno porque el string de la ruta se guardaria en el reader
    std::string map;
    int water_level;
    b2World world;
    GameBuilder builder;
    std::vector<Worm> players;
    int turn;

public:
    Game(std::string map_route): world(b2Vec2(0.0f, -10.0f)), builder(world), turn(0) {}

    Snapshot start_and_send() {
        MapReader map_reader(map); 
        Snapshot snapshot = map_reader.read_map();
        builder.create_map(snapshot);
        return snapshot;
    }

    void add_player(int current_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = nullptr;
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