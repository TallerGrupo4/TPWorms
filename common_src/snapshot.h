#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <string>
#include <vector>
#include <map>
#include "constants.h"
#include "provision_box_snapshot.h"
#include "projectile_snapshot.h"
#include "worm_snapshot.h"
#include "platform_snapshot.h"
#include "../server_src/config.h"
#include "../server_src/game_src/game_constants.h"

struct MapDimensions {
    float height = DEFAULT;
    float width = DEFAULT;
    float worm_width = WORM_WIDTH;
    float worm_height = WORM_HEIGHT;
    int amount_of_worms = DEFAULT;
    int water_level = DEFAULT;
} typedef MapDimensions_t;

struct TurnTimeAndWormTurn {
    uint turn_time = DEFAULT;
    char worm_turn = DEFAULT;
} typedef TurnTimeAndWormTurn_t;
 

class Snapshot {
    bool end_game = false;
    int wind_force = 0;
public:
    std::vector<WormSnapshot> worms;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<PlatformSnapshot> platforms;
    std::vector<ProvisionBoxSnapshot> provision_boxes;
    std::map<char, std::vector<char>> my_army;
    MapDimensions_t map_dimensions;
    TurnTimeAndWormTurn_t turn_time_and_worm_turn;
    std::map<char, int> armies_health;

    Snapshot(std::vector<WormSnapshot> worms, std::vector<ProjectileSnapshot> projectiles, std::vector<PlatformSnapshot> platforms, std::vector<ProvisionBoxSnapshot> provision_boxes):
            worms(worms), projectiles(projectiles) , platforms(platforms), provision_boxes(provision_boxes), map_dimensions() {};
    
    Snapshot() {};
    ~Snapshot() {};

    void set_dimensions(float height = 0, float width = 0, float worm_width = WORM_WIDTH, float worm_height = WORM_HEIGHT, int amount_of_worms = 0, int water_level = 0) {
        map_dimensions.height = height;
        map_dimensions.width = width;
        map_dimensions.worm_width = worm_width;
        map_dimensions.worm_height = worm_height;
        map_dimensions.amount_of_worms = amount_of_worms;
        map_dimensions.water_level = water_level;
    }
    void set_turn_time_and_worm_turn(int turn_time = 0, int worm_turn = 0) {
        turn_time_and_worm_turn.turn_time = turn_time;
        turn_time_and_worm_turn.worm_turn = worm_turn;
    }

    void set_armies_health(std::map<char, int> armies_health) {
        this->armies_health = armies_health;
    }

    void set_end_game() {
        end_game = true;
    }

    void set_wind_force(int wind_force) {
        this->wind_force = wind_force;
    }

    int get_wind_force() {
        return wind_force;
    }

    bool get_end_game() {
        return end_game;
    }
};

#endif  // SNAPSHOT_H