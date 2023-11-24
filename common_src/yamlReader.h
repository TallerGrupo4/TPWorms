#include <yaml-cpp/yaml.h>
#include <vector>
#include "snapshot.h"
#include <iostream> 

#ifndef YAML_READER_H
#define YAML_READER_H



// Para facilitar el uso de los beams en los YAMLs
namespace YAML {
template<>
struct convert<BeamType> {
    static bool decode(const YAML::Node& node, BeamType& value) {
        if (node.IsScalar()) {
            std::string typeStr = node.as<std::string>();
            static const std::unordered_map<std::string, BeamType> typeMap{
                {"LargeVertical", LargeVertical},
                {"Large65", Large65},
                {"Large45", Large45},
                {"Large25", Large25},
                {"LargeHorizontal", LargeHorizontal},
                {"LargeMinus25", LargeMinus25},
                {"LargeMinus45", LargeMinus45},
                {"LargeMinus65", LargeMinus65},
                {"LargeVerticalFlipped", LargeVerticalFlipped},
                {"ShortVertical", ShortVertical},
                {"Short65", Short65},
                {"Short45", Short45},
                {"Short25", Short25},
                {"ShortHorizontal", ShortHorizontal},
                {"ShortMinus25", ShortMinus25},
                {"ShortMinus45", ShortMinus45},
                {"ShortMinus65", ShortMinus65},
                {"ShortVerticalFlipped", ShortVerticalFlipped}
            };

            auto it = typeMap.find(typeStr);
            if (it != typeMap.end()) {
                value = it->second;
                return true;
            }
        }
        return false; // Invalid enum value
    }
};
}

class Reader {
    protected: 
    YAML::Node node;
    public:
        Reader(std::string route){
            node = YAML::LoadFile(route);
        }
};

class MapReader : public Reader {

    public:
        MapReader(std::string route): Reader(route) {}
        Snapshot read_map () {
            std::vector<PlatformSnapshot> platforms_snap;
            YAML::Node platforms = node["platforms"];
            for (YAML::const_iterator it = platforms.begin(); it != platforms.end(); ++it) {

                // Has type , x , y
                YAML::Node platform = *it;
                BeamType type =platform["type"].as<BeamType>();
                float x = platform["x"].as<float>();
                float y = platform["y"].as<float>();
                float width = platform["width"].as<float>();
                float height = platform["height"].as<float>();
                platforms_snap.push_back(PlatformSnapshot(type, x, y, width, height));
            }
            Snapshot map_snap({}, platforms_snap);
            YAML::Node dimensions = node["dimensions"];
            int height = dimensions[0]["height"].as<int>();
            int width = dimensions[0]["width"].as<int>();
            int amount_of_worms = dimensions[0]["amount_of_worms"].as<int>();
            map_snap.set_dimensions(width, height, WORM_WIDTH, WORM_HEIGHT, amount_of_worms);
            return map_snap;
        }

};

//TODO
class SettingsReader: public Reader {
    SettingsReader(std::string route): Reader(route) {}
};

#endif //YAML_READER_H