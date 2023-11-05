#include <box2d/box2d.h>

#define PLAT_SMALL 6
#define PLAT_BIG 3
#define PLAT_HEIGHT 0.8
#define PLAT_FRICTION 0.5

#define PLAYER_WIDTH 0.5
#define PLAYER_HEIGHT 1.5
#define PLAYER_FRICTION 0.5

#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

class GameBuilder {
    b2World& world;

    void create_platform(float x, float y, float width, float height){
        b2BodyDef platform_def;
        platform_def.type = b2_staticBody;
        platform_def.position.Set(x, y);
        b2Body* platform = world.CreateBody(&platform_def);
        b2PolygonShape platform_shape;
        platform_shape.SetAsBox(width/2, height/2);
        b2FixtureDef platform_fixture;
        platform_fixture.shape = &platform_shape;
        platform_fixture.friction = PLAT_FRICTION;
        platform->CreateFixture(&platform_fixture);
    }

    public:
    GameBuilder(b2World& world) : world(world) {}


    void create_small_platform(float x, float y){
        create_platform(x, y, PLAT_SMALL, PLAT_HEIGHT);
    }

    void create_big_platform(float x, float y){
        create_platform(x, y, PLAT_BIG, PLAT_HEIGHT);
    }

    b2Body* create_worm(float x , float y){ //TODO: Create Class Worm
        b2BodyDef worm_def;
        worm_def.type = b2_dynamicBody;
        worm_def.position.Set(x, y);
        worm_def.fixedRotation = true;
        b2Body* worm = world.CreateBody(&worm_def);
        b2PolygonShape worm_shape;
        worm_shape.SetAsBox(PLAYER_WIDTH/2, PLAYER_HEIGHT/2);
        b2FixtureDef worm_fixture;
        worm_fixture.shape = &worm_shape;
        worm_fixture.friction = PLAYER_FRICTION;
        worm->CreateFixture(&worm_fixture);
        return worm;
    }
};

#endif

