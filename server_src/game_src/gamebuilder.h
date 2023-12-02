#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <box2d/box2d.h>
#include "../../common_src/snapshot.h"
#include "../../common_src/constants.h"
#include "game_constants.h"
#include "beam.h"
#include "../config.h"

#define PLAT_FRICTION ConfigSingleton::getInstance().get_plat_friction()
#define PLAT_SMALL ConfigSingleton::getInstance().get_plat_small()
#define PLAT_BIG ConfigSingleton::getInstance().get_plat_big()
#define PLAT_HEIGHT ConfigSingleton::getInstance().get_plat_height()
#define WORM_WIDTH ConfigSingleton::getInstance().get_worm_width()
#define WORM_HEIGHT ConfigSingleton::getInstance().get_worm_height()
#define WORM_FRICTION ConfigSingleton::getInstance().get_worm_friction()

class GameBuilder {
    std::vector<std::shared_ptr<Beam>> beams;
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

    b2Body* create_projectile_body(float angle , float x , float y, float restitution, float density);

    b2Body* create_fragment_body(b2Body* father_body, float angle);

    b2Body* create_provision_box_body(float x , float y);

    ~GameBuilder();

};

#endif
