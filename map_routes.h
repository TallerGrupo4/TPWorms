#include <vector>
#include <list>
#include <string>
#include <filesystem>

#ifndef MAP_ROUTES_H
#define MAP_ROUTES_H

class MapRoutes {
private:
    std::list<std::string> routes;

public:
    MapRoutes() {
        // Path to the folder containing the YAML files while being inside build (monitor_matches uses this)
        std::string folderPath = "../external/maps";
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.path().extension() == ".yaml") {
                routes.push_front(entry.path().string());
            }
        }
    }

    std::vector<std::string> get_routes() {
        std::vector<std::string> routes_vector;
        for (auto& route : routes) {
            routes_vector.push_back(route);
        }
        return routes_vector;
    }

    ~MapRoutes() {}
};

#endif  // MAP_ROUTES_H
