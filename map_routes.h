#include <algorithm>
#include <filesystem>
#include <list>
#include <string>
#include <vector>

#ifndef MAP_ROUTES_H
#define MAP_ROUTES_H

class MapRoutes {
private:
    std::string maps_path;
    std::list<std::string> routes;

public:
    explicit MapRoutes(std::string maps_path): maps_path(maps_path) {
        // Path to the folder containing the YAML files while being inside build (monitor_matches
        // uses this)
        for (const auto& entry: std::filesystem::directory_iterator(maps_path)) {
            if (entry.path().extension() == ".yaml") {
                routes.push_front(entry.path().string());
            }
        }
    }

    std::vector<std::string> get_routes() {
        std::vector<std::string> routes_vector;
        std::copy(routes.begin(), routes.end(), std::back_inserter(routes_vector));
        return routes_vector;
    }

    ~MapRoutes() {}
};

#endif  // MAP_ROUTES_H
