#include <box2d/box2d.h>
#include <yaml-cpp/yaml.h>

#include "../../common_src/snapshot.h"

#define PLAT_SMALL 3
#define PLAT_BIG 6
#define PLAT_HEIGHT 0.8
#define PLAT_FRICTION 0.5

#define PLAYER_WIDTH 1
#define PLAYER_HEIGHT 1
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


    Snapshot create_map(std::string map_name) {
        std::vector<PlatformSnapshot> platforms_snap;
        std::string route = "../../external/";
        route += map_name;
        route += ".yaml";
        YAML::Node map = YAML::LoadFile(route);
        YAML::Node platforms = map["platforms"];
        for (YAML::const_iterator it = platforms.begin(); it != platforms.end(); ++it) {
            // Has type , x , y
            YAML::Node platform = *it;
            float x = platform["x"].as<float>();
            float y = platform["y"].as<float>();
            BeamType type = (BeamType)platform["type"].as<char>();
            create_platform_type(x, y, type);
            if (type <= 8) { //Esto es para no hacer un switch gigantezco devuelta
                PlatformSnapshot snap(type, x - PLAT_BIG/2, y + PLAT_HEIGHT/2);
                platforms_snap.push_back(snap);
            } else {
                PlatformSnapshot snap(type, x - PLAT_SMALL/2, y + PLAT_HEIGHT);
                platforms_snap.push_back(snap);
            }
        }
        YAML::Node dimensions = map["dimensions"];
        int width = dimensions["width"].as<int>();
        int height = dimensions["height"].as<int>();
        Snapshot map_snap({},platforms_snap);
        map_snap.set_dimensions(width, height);

        return map_snap;
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
