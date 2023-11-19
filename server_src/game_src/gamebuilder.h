#include <box2d/box2d.h>
#include <yaml-cpp/yaml.h>

#include "../../common_src/snapshot.h"

#define PLAT_SMALL 3
#define PLAT_BIG 6
#define PLAT_HEIGHT 0.8
#define PLAT_FRICTION 0.5

#define PLAYER_WIDTH 2
#define PLAYER_HEIGHT 2
#define PLAYER_FRICTION 0.5

#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H


#define DEG_TO_RAD 0.0174532925199432957f

class GameBuilder {
    b2World& world;

    void create_platform(float x, float y, float width, float height, float angle) {
        b2BodyDef platform_def;
        platform_def.type = b2_staticBody;
        platform_def.position.Set(x, y);
        b2Body* platform = world.CreateBody(&platform_def);
        b2PolygonShape platform_shape;
        platform_shape.SetAsBox(width / 2, height / 2);
        b2FixtureDef platform_fixture;
        platform_fixture.shape = &platform_shape;
        platform_fixture.friction = PLAT_FRICTION;
        platform->CreateFixture(&platform_fixture);
    }

public:
    GameBuilder(b2World& world): world(world) {}


    void create_map(Snapshot& map_snap) {
        for (PlatformSnapshot platform : map_snap.platforms) {
            create_platform_type(platform.pos_x, platform.pos_y, platform.type);
        }
        create_walls(b2Vec2_zero , map_snap.width , map_snap.height);

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
        create_wall(b2Vec2(center_world.x - width/2 , center_world.y) , height_world , 90 * DEGTORAD);
        create_wall(b2Vec2(center_world.x + width/2 , center_world.y) , height_world, 90 * DEGTORAD);
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
        worm_def.fixedRotation = true;
        b2Body* worm = world.CreateBody(&worm_def);
        b2PolygonShape worm_shape;
        worm_shape.SetAsBox(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);
        b2FixtureDef worm_fixture;
        worm_fixture.density = 1;
        worm_fixture.shape = &worm_shape;
        worm_fixture.friction = PLAYER_FRICTION;
        worm->CreateFixture(&worm_fixture);
        return worm;
    }



    void create_platform_type(float x , float y, BeamType type){
        switch (type){
            case LargeVertical:
                create_big_platform(x, y, 90 * DEG_TO_RAD);
                break;
            case Large65:
                create_big_platform(x, y, 65 * DEG_TO_RAD);
                break;
            case Large45:
                create_big_platform(x, y, 45 * DEG_TO_RAD);
                break;
            case Large25:
                create_big_platform(x, y, 25 * DEG_TO_RAD);
                break;
            case LargeHorizontal:
                create_big_platform(x, y, 0);
                break;
            case LargeMinus25:
                create_big_platform(x, y, -25 * DEG_TO_RAD);
                break;
            case LargeMinus45:
                create_big_platform(x, y, -45 * DEG_TO_RAD);
                break;
            case LargeMinus65:
                create_big_platform(x, y, -65 * DEG_TO_RAD);
                break;
            case LargeVerticalFlipped:
                create_big_platform(x, y, -90 * DEG_TO_RAD);
                break;
            case ShortVertical:
                create_small_platform(x, y, 90 * DEG_TO_RAD);
                break;
            case Short65:
                create_small_platform(x, y, 65 * DEG_TO_RAD);
                break;
            case Short45:
                create_small_platform(x, y, 45 * DEG_TO_RAD);
                break;
            case Short25:
                create_small_platform(x, y, 25 * DEG_TO_RAD);
                break;
            case ShortHorizontal:
                create_small_platform(x, y, 0);
                break;
            case ShortMinus25:
                create_small_platform(x, y, -25 * DEG_TO_RAD);
                break;
            case ShortMinus45:
                create_small_platform(x, y, -45 * DEG_TO_RAD);
                break;
            case ShortMinus65:
                create_small_platform(x, y, -65 * DEG_TO_RAD);
                break;
            case ShortVerticalFlipped:
                create_small_platform(x, y, -90 * DEG_TO_RAD);
                break;
        }  
    }


};

#endif
