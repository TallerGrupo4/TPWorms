#include <string>
#include <vector>

#include <box2d/box2d.h>

#include "../common_src/snapshot.h"

#ifndef MAP_H
#define MAP_H

class Map {
public:
    std::string name;
    int width;
    int height;
    int amount_of_worms;
    std::vector<PlatformSnapshot> platforms;
    std::vector<b2Vec2> spawn_points;
    float water_level;

    Map(int width, int height, int amount_of_worms, const std::vector<PlatformSnapshot>& platforms,
        const std::vector<b2Vec2>& spawn_points, float water_level, const std::string& name);

    Snapshot get_snapshot() const;

    Map() {}
    ~Map();
};

#endif  // MAP_H
