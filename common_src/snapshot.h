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


    WormSnapshot(char id, float pos_x, float pos_y, int angle, int max_health, int health, char direction, int weapon,
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
    float width;  // cast to int in client
    float height;  // This one is always the same

    PlatformSnapshot(BeamType type, float pos_x, float pos_y, float width = PLAT_SMALL, float height = PLAT_HEIGHT):
            type(type), pos_x(pos_x), pos_y(pos_y), width(width), height(height) {};
    ~PlatformSnapshot(){};
};
 

class Snapshot {
public:
    std::vector<WormSnapshot> worms;
    std::vector<PlatformSnapshot> platforms;
    // std::vector<ProjectileSnapshot> projectiles;
    float height;
    float width;
    float worm_width;
    float worm_height;

    Snapshot(std::vector<WormSnapshot> worms, std::vector<PlatformSnapshot> platforms, float height = 0, float width = 0, float worm_width = WORM_WIDTH, float worm_height = WORM_HEIGHT):
            worms(worms), platforms(platforms), height(height), width(width), worm_width(worm_width), worm_height(worm_height) {};
    
    Snapshot() {};
    ~Snapshot() {};

    void set_dimensions(int height, int width){
        this->height = height ;
        this->width = width;
    }
};

#endif  // SNAPSHOT_H