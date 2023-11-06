#include <box2d/box2d.h>
#include <vector>
#include <string>
#include "../../common_src/constants.h"
#include "gamebuilder.h"
#include "snapshot.h"
#include "worm.h"

#ifndef GAME_H
#define GAME_H

class Game{
    std::string map;
    int water_level;
    b2World world;
    GameBuilder builder;
    std::vector<Worm> players;
    int turn;
    
    public:
    Game(std::string map_route): world(b2Vec2(0.0f, -10.0f)), builder(world), turn(0) {
    }

    MapSnapshot start_and_send(){
        return builder.create_map(map);
    }

    void add_player(int current_id){ //TODO: ADD ARMY INSTEAD OF PLAYERS
        b2Body* player = builder.create_worm(0, 1); // TODO: randomize position
        players.push_back(Worm(current_id, player));
    }

    void move_player(int id, int direction){
        Worm player = players[id];
        player.move(direction);
    }

    void step(){
        world.Step(1.0f / 60.0f, 8, 3);
    }

    GameSnapshot get_game_snapshot(){
        std::vector<WormSnapshot> worms;
        for (Worm& worm : players){
            worms.push_back(worm.get_snapshot());
        }
        GameSnapshot snapshot(worms);
        return snapshot;
    }

    
};

#endif //GAME_H