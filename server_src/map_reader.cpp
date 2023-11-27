#include "map_reader.h"

MapReader::MapReader(std::string route): Reader(route) {}

Map  MapReader::read_map () {
    std::vector<PlatformSnapshot> platforms_snap = read_platforms();
    std::vector<b2Vec2> spawn_points = read_spawn_points();

    YAML::Node dimensions = node["dimensions"];
    int height = dimensions[0]["height"].as<int>();
    int width = dimensions[0]["width"].as<int>();
    int amount_of_worms = dimensions[0]["amount_of_worms"].as<int>();
    int water_level = dimensions[0]["water_level"].as<float>();

    return Map(width, height, amount_of_worms, platforms_snap, spawn_points, water_level);
}

std::vector<PlatformSnapshot>  MapReader::read_platforms(){
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
    return platforms_snap;
}

std::vector<b2Vec2>  MapReader::read_spawn_points(){
    std::vector<b2Vec2> spawn_points;
    YAML::Node spawn_points_node = node["spawn_points"];
    for (YAML::const_iterator it = spawn_points_node.begin(); it != spawn_points_node.end(); ++it) {
        YAML::Node spawn_point = *it;
        float x = spawn_point["x"].as<float>();
        float y = spawn_point["y"].as<float>();
        spawn_points.push_back(b2Vec2(x, y));
    }
    return spawn_points;
}

