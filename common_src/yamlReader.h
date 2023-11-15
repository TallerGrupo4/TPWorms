#include <yaml-cpp/yaml.h>
#include <vector>
#include "snapshot.h"

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
                float x = platform["x"].as<float>();
                float y = platform["y"].as<float>();
                BeamType type =platform["type"].as<BeamType>();
                platforms_snap.push_back(PlatformSnapshot(type, x, y));
            }
            Snapshot map_snap({}, platforms_snap);
            YAML::Node dimensions = node["dimensions"];
            int width = dimensions["width"].as<int>();
            int height = dimensions["height"].as<int>();
            map_snap.set_dimensions(width, height);
            return map_snap;
        }

};

//TODO
class SettingsReader: public Reader {
    SettingsReader(std::string route): Reader(route) {}
};

#endif //YAML_READER_H