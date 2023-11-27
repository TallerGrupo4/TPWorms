#include <box2d/box2d.h>
#include "../../common_src/snapshot.h"
#include "../../common_src/constants.h"

#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

class GameBuilder {
    b2World& world;

    float calculate_plat_frict(float angle);

    void create_platform(float x, float y, float width, float height, float angle);

    void create_wall(b2Vec2 coords , float width, float angle);

    void create_walls(b2Vec2 center_world,  float width , float height_world);

    void create_small_platform(float x, float y, float angle);

    void create_big_platform(float x, float y, float angle);

    void create_platform_type(float x , float y, BeamType type);

public:
    GameBuilder(b2World& world);

    void create_map(Snapshot& map_snap);

    b2Body* create_worm(float x, float y);

    ~GameBuilder();

};

#endif
