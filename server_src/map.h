#include "../common_src/snapshot.h"
#include "../common_src/yamlReader.h"
#include <vector>

#ifndef MAP_H
#define MAP_H

class Map {
    public:
    int width;
    int height;
    int amount_of_worms;
    std::vector<PlatformSnapshot> platforms;

    Map(std::string map_route) {
        MapReader map_reader(map_route); 
        Snapshot snapshot = map_reader.read_map();
        width = snapshot.map_dimensions.width;
        height = snapshot.map_dimensions.height;
        amount_of_worms = snapshot.map_dimensions.amount_of_worms;
        platforms = snapshot.platforms;
    }

    Map() {};
    ~Map() {};

};

#endif //MAP_H