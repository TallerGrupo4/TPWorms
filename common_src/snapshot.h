#include <string>
#include <vector>
#include <map>
#include "constants.h"


#ifndef SNAPSHOT_H
#define SNAPSHOT_H

struct MapDimensions {
    float height = DEFAULT;
    float width = DEFAULT;
    float worm_width = WORM_WIDTH;
    float worm_height = WORM_HEIGHT;
    int amount_of_worms = DEFAULT;
} typedef MapDimensions_t;

struct TurnTimeAndWormTurn {
    uint turn_time = DEFAULT;
    char worm_turn = DEFAULT;
} typedef TurnTimeAndWormTurn_t;

enum BeamType : char {
    LargeVertical, // 0
    Large65,
    Large45,
    Large25,
    LargeHorizontal,
    LargeMinus25,
    LargeMinus45,
    LargeMinus65,
    LargeVerticalFlipped, // 8
    ShortVertical,
    Short65,
    Short45,
    Short25,
    ShortHorizontal,
    ShortMinus25,
    ShortMinus45,
    ShortMinus65,
    ShortVerticalFlipped, // 17
};

class ProjectileSnapshot {
    public:
    float pos_x;
    float pos_y;
    float angle; // Remove this, I think it is never been used (it is setted in the server but in the client it's never used)
    int type;

    ProjectileSnapshot(int type, float pos_x, float pos_y, float angle):
            pos_x(pos_x), pos_y(pos_y), angle(angle), type(type) {};

};

class WormSnapshot {
public:
    char id;
    float pos_x;
    float pos_y;
    int angle;
    int max_health;
    int health;
    char direction;
    int weapon;
    int state;
    char team_id;


    WormSnapshot(char id, float pos_x, float pos_y, int angle, int max_health, int health, char direction, int weapon,
                 int state, char team_id):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            angle(angle),
            max_health(max_health),
            health(health),
            direction(direction),
            weapon(weapon),
            state(state), 
            team_id(team_id) {};
    ~WormSnapshot(){};
};

class PlatformSnapshot {
public:
    BeamType type;
    float pos_x;
    float pos_y;
    float width;
    float height;


    PlatformSnapshot(BeamType type, float pos_x, float pos_y, float width = PLAT_SMALL, float height = PLAT_HEIGHT):
            type(type), pos_x(pos_x), pos_y(pos_y), width(width), height(height) {};
    ~PlatformSnapshot(){};
};
 

class Snapshot {
public:
    std::vector<WormSnapshot> worms;
    std::vector<PlatformSnapshot> platforms;
    // std::vector<ProjectileSnapshot> projectiles;
    std::map<char, std::vector<char>> my_army;
    MapDimensions_t map_dimensions;
    TurnTimeAndWormTurn_t turn_time_and_worm_turn;

    Snapshot(std::vector<WormSnapshot> worms, std::vector<PlatformSnapshot> platforms):
            worms(worms), platforms(platforms), map_dimensions() {};
    
    Snapshot() {};
    ~Snapshot() {};

    void set_dimensions(float height = 0, float width = 0, float worm_width = WORM_WIDTH, float worm_height = WORM_HEIGHT, int amount_of_worms = 0) {
        map_dimensions.height = height;
        map_dimensions.width = width;
        map_dimensions.worm_width = worm_width;
        map_dimensions.worm_height = worm_height;
        map_dimensions.amount_of_worms = amount_of_worms;
    }
    void set_turn_time_and_worm_turn(int turn_time = 0, int worm_turn = 0) {
        turn_time_and_worm_turn.turn_time = turn_time;
        turn_time_and_worm_turn.worm_turn = worm_turn;
    }
};

#endif  // SNAPSHOT_H