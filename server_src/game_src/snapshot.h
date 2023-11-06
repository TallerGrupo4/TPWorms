#include <vector>
#include <string>

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class WormSnapshot{
    int id;
    float pos_x;
    float pos_y;
    float angle;
    int life;
    int direction;
    int weapon;
    int state;

    public:
    WormSnapshot(int id, float pos_x, float pos_y, float angle, int life, int direction, int weapon, int state): id(id), pos_x(pos_x), pos_y(pos_y), angle(angle), life(life), direction(direction), weapon(weapon), state(state){};
    ~WormSnapshot(){};

    int get_id(){
        return id;
    }

    float get_pos_x(){
        return pos_x;
    }

    float get_pos_y(){
        return pos_y;
    }

    float get_angle(){
        return angle;
    }

    int get_life(){
        return life;
    }

    int get_direction(){
        return direction;
    }

    int get_weapon(){
        return weapon;
    }

    int get_state(){
        return state;
    }
};

class GameSnapshot{
    std::vector<WormSnapshot> worms;
    // std::vector<ProjectileSnapshot> projectiles;

    public: 
    GameSnapshot(std::vector<WormSnapshot> worms): worms(worms){};
    ~GameSnapshot(){};

    std::vector<WormSnapshot> get_worms(){
        return worms;
    }

    // std::vector<ProjectileSnapshot> get_projectiles(){
    //     return projectiles;
    // }
};

class PlatformSnapshot{
    float pos_x;
    float pos_y;
    float angle;
    int width;
    int height;

    public:
    PlatformSnapshot(float pos_x, float pos_y, float angle , int width, int height): pos_x(pos_x), pos_y(pos_y), angle(angle) , width(width), height(height){};
    ~PlatformSnapshot(){};

    float get_pos_x(){
        return pos_x;
    }

    float get_pos_y(){
        return pos_y;
    }

    int get_width(){
        return width;
    }

    int get_height(){
        return height;
    }
};

class MapSnapshot {
    std::vector<PlatformSnapshot> platforms;

    public:

    MapSnapshot(std::vector<PlatformSnapshot> platforms): platforms(platforms){};
    ~MapSnapshot(){};

    std::vector<PlatformSnapshot> get_platforms(){
        return platforms;
    }

};

#endif //SNAPSHOT_H