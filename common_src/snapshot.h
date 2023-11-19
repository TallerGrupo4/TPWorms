#include <string>
#include <vector>
#include "constants.h"


#ifndef SNAPSHOT_H
#define SNAPSHOT_H

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
    float angle;
    int type;

    ProjectileSnapshot(int type, float pos_x, float pos_y, float angle):
            pos_x(pos_x), pos_y(pos_y), angle(angle), type(type) {};

};

class WormSnapshot {
public:
    char id;
    float pos_x;
    float pos_y;
    float angle;
    int max_health;
    int health;
    char direction;
    int weapon;
    int state;


    WormSnapshot(char id, float pos_x, float pos_y, float angle, int max_health, int health, char direction, int weapon,
                 int state):
            id(id),
            pos_x(pos_x),
            pos_y(pos_y),
            angle(angle),
            max_health(max_health),
            health(health),
            direction(direction),
            weapon(weapon),
            state(state){};
    ~WormSnapshot(){};
};

class PlatformSnapshot {
public:
    BeamType type;
    float pos_x;
    float pos_y;
    

    PlatformSnapshot(BeamType type, float pos_x, float pos_y):
            type(type), pos_x(pos_x), pos_y(pos_y) {};
    ~PlatformSnapshot(){};
};
 

class Snapshot {
public:
    std::vector<WormSnapshot> worms;
    std::vector<PlatformSnapshot> platforms;
    // std::vector<ProjectileSnapshot> projectiles;
    float height = 0;
    float width = 0;

    Snapshot(std::vector<WormSnapshot> worms, std::vector<PlatformSnapshot> platforms):
            worms(worms), platforms(platforms) {};
    
    Snapshot() {};
    ~Snapshot() {};

    void set_dimensions(int height, int width){
        this->height = height ;
        this->width = width;
    }
};

#endif  // SNAPSHOT_H