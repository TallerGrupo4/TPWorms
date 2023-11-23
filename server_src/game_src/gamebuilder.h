#include <box2d/box2d.h>
#include <yaml-cpp/yaml.h>

#include "../../common_src/snapshot.h"
#include "../../common_src/constants.h"

#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

class GameBuilder {
    b2World& world;


    float calculate_plat_frict(float angle){
        float friction = 0;
        if (abs(angle) > 45){
            return friction;
        } else {
            friction = (abs(angle) * 0.02f) + PLAT_FRICTION;
            return friction;
        }
    }

    void create_platform(float x, float y, float width, float height, float angle) {
        b2BodyDef platform_def;
        platform_def.type = b2_staticBody;
        platform_def.position.Set(x, y);
        platform_def.angle = angle * DEGTORAD;
        b2Body* platform = world.CreateBody(&platform_def);
        b2PolygonShape platform_shape;
        platform_shape.SetAsBox(width / 2, height / 2);
        b2FixtureDef platform_fixture;
        platform_fixture.shape = &platform_shape;
        platform_fixture.friction = calculate_plat_frict(angle);
        platform->CreateFixture(&platform_fixture);
    }

public:
    GameBuilder(b2World& world): world(world) {}


    void create_map(Snapshot& map_snap) {
        for (PlatformSnapshot platform : map_snap.platforms) {
            // Add width and height to platform
            create_platform_type(platform.pos_x, platform.pos_y, platform.type);
        }
        create_walls(b2Vec2_zero , map_snap.map_dimensions.width , map_snap.map_dimensions.height);

    }

    void create_wall(b2Vec2 coords , float width, float angle){
        b2BodyDef wall;
        wall.type = b2_staticBody;
        wall.position.Set(coords.x, coords.y);
        wall.angle = angle;
        b2Body* wall_body = world.CreateBody(&wall);
        b2PolygonShape wall_shape;
        wall_shape.SetAsBox(width/2, 0.1);
        b2FixtureDef wall_fixture;
        wall_fixture.shape = &wall_shape;

        wall_fixture.friction = 0.5;
        wall_body->CreateFixture(&wall_fixture);
    }

    void create_walls(b2Vec2 center_world,  float width , float height_world){
        create_wall(b2Vec2(center_world.x - width/2 , center_world.y) , height_world , 90);
        create_wall(b2Vec2(center_world.x + width/2 , center_world.y) , height_world, 90);
        create_wall(b2Vec2(center_world.x , center_world.y - height_world/2) , width, 0);
        create_wall(b2Vec2(center_world.x , center_world.y + height_world/2) , width, 0);
    }

    void create_small_platform(float x, float y, float angle) {
        create_platform(x, y, PLAT_SMALL, PLAT_HEIGHT , angle);
    }

    void create_big_platform(float x, float y, float angle) {
        create_platform(x, y, PLAT_BIG, PLAT_HEIGHT , angle);
    }

    b2Body* create_worm(float x, float y) {  // TODO: Create Class Worm
        b2BodyDef worm_def;
        worm_def.type = b2_dynamicBody;
        worm_def.position.Set(x, y);
        b2Body* worm = world.CreateBody(&worm_def);
        b2PolygonShape worm_shape;
        worm_shape.SetAsBox(WORM_WIDTH / 2.0f, WORM_HEIGHT / 2.0f);
        b2FixtureDef worm_fixture;
        worm_fixture.density = 1;
        worm_fixture.shape = &worm_shape;
        worm_fixture.friction = WORM_FRICTION;
        worm->CreateFixture(&worm_fixture);
        return worm;
    }



    void create_platform_type(float x , float y, BeamType type){
        switch (type){
            case LargeVertical:
                create_big_platform(x, y, 90);
                break;
            case Large65:
                create_big_platform(x, y, 65);
                break;
            case Large45:
                create_big_platform(x, y, 45);
                break;
            case Large25:
                create_big_platform(x, y, 25);
                break;
            case LargeHorizontal:
                create_big_platform(x, y, 0);
                break;
            case LargeMinus25:
                create_big_platform(x, y, -25);
                break;
            case LargeMinus45:
                create_big_platform(x, y, -45);
                break;
            case LargeMinus65:
                create_big_platform(x, y, -65);
                break;
            case LargeVerticalFlipped:
                create_big_platform(x, y, -90);
                break;
            case ShortVertical:
                create_small_platform(x, y, 90);
                break;
            case Short65:
                create_small_platform(x, y, 65);
                break;
            case Short45:
                create_small_platform(x, y, 45);
                break;
            case Short25:
                create_small_platform(x, y, 25);
                break;
            case ShortHorizontal:
                create_small_platform(x, y, 0);
                break;
            case ShortMinus25:
                create_small_platform(x, y, -25);
                break;
            case ShortMinus45:
                create_small_platform(x, y, -45);
                break;
            case ShortMinus65:
                create_small_platform(x, y, -65);
                break;
            case ShortVerticalFlipped:
                create_small_platform(x, y, -90);
                break;
        }  
    }


};

#endif
