#include "map.h"


Map::Map(int width, int height, int amount_of_worms, const std::vector<PlatformSnapshot>& platforms,
         const std::vector<b2Vec2>& spawn_points, float water_level, const std::string& name):
        name(name),
        width(width),
        height(height),
        amount_of_worms(amount_of_worms),
        platforms(platforms),
        spawn_points(spawn_points),
        water_level(water_level) {}

Snapshot Map::get_snapshot() const {
    Snapshot snapshot({}, {}, platforms, {});
    snapshot.set_dimensions(height, width, WORM_WIDTH, WORM_HEIGHT, amount_of_worms, water_level);
    return snapshot;
}

Map::~Map() {}
