#include <string>
#include <vector>

#include <box2d/box2d.h>

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"

#include "gamebuilder.h"
#include "worm.h"

#ifndef GAME_H
#define GAME_H

class GameCommand;


class Game {
    std::string map;
    int water_level;
    b2World world;
    GameBuilder builder;
    std::vector<Worm> players;
    int turn;

public:
    Game(std::string map_route): world(b2Vec2(0.0f, -10.0f)), builder(world), turn(0) {}

    Snapshot start_and_send() { return builder.create_map(map); }

    void add_player(int current_id) {  // TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = nullptr;
        players.push_back(Worm(current_id, player));
    }

    void move_player(char id, int direction) {
        Worm player = players[id];
        player.move(direction);
    }

    //  


    void step() { world.Step(1.0f / 60.0f, 8, 3); }

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