#include "../common_src/snapshot.h"
#include <box2d/box2d.h>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Map {
    public:
    int width;
    int height;
    int amount_of_worms;
    std::vector<PlatformSnapshot> platforms;
    std::vector<b2Vec2> spawn_points;
    float water_level;

    Map(int width , int height , int amount_of_worms , std::vector<PlatformSnapshot> platforms , std::vector<b2Vec2> spawn_points, float water_level):
        width(width),
        height(height),
        amount_of_worms(amount_of_worms),
        platforms(platforms),
        spawn_points(spawn_points),
        water_level(water_level) {
    }

    Snapshot get_snapshot(){
        Snapshot snapshot({}, platforms, {});
        snapshot.set_dimensions(height, width, WORM_WIDTH, WORM_HEIGHT, amount_of_worms);
        return snapshot;
    }

    Map() {};
    ~Map() {};

};

#endif //MAP_H