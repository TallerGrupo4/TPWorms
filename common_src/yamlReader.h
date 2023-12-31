#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "snapshot.h"


#ifndef YAML_READER_H
#define YAML_READER_H


namespace YAML {
template <>
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
                    {"ShortVerticalFlipped", ShortVerticalFlipped}};

            auto it = typeMap.find(typeStr);
            if (it != typeMap.end()) {
                value = it->second;
                return true;
            }
        }
        return false;
    }
};
}  // namespace YAML

class Reader {
protected:
    YAML::Node node;

public:
    explicit Reader(const std::string& route): node(YAML::LoadFile(route)) {}
};


#endif  // YAML_READER_H
