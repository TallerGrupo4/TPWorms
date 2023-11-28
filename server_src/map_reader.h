#include <box2d/box2d.h>
#include "../common_src/yamlReader.h"
#include "map.h"

#ifndef MAP_READER_H
#define MAP_READER_H

class MapReader : public Reader {

    public:
        MapReader(std::string route);
        Map read_map ();

        std::vector<PlatformSnapshot> read_platforms();

        std::vector<b2Vec2> read_spawn_points();

};

#endif  // MAP_READER_H
