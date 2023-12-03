#include "gamebuilder.h"

float GameBuilder::calculate_plat_frict(float angle){
    float friction = 0;
    if (abs(angle) > 45 && abs(angle) != 90){
        return friction;
    } else {
        friction = (abs(angle) * 0.02f) + PLAT_FRICTION;
        while (friction > 1){
            friction -= 1;
        }
        return friction;
    }
}

void GameBuilder::create_platform(float x, float y, float width, float height, float angle) {
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
    platform_fixture.restitution = 0;
    platform->CreateFixture(&platform_fixture);
    std::shared_ptr<Beam> beam = std::make_shared<Beam>(platform);
    beams.push_back(beam);
}

GameBuilder::GameBuilder(b2World& world): world(world) {}
GameBuilder::~GameBuilder() {}

void GameBuilder::create_map(Snapshot& map_snap) {
    for (PlatformSnapshot platform : map_snap.platforms) {
        create_platform_type(platform.pos_x, platform.pos_y, platform.type);
    }
    create_walls(b2Vec2_zero , map_snap.map_dimensions.width , map_snap.map_dimensions.height);

}

void GameBuilder::create_wall(b2Vec2 coords , float width, float angle){
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

    std::shared_ptr<Beam> beam = std::make_shared<Beam>(wall_body);
    beams.push_back(beam);
}

void GameBuilder::create_walls(b2Vec2 center_world,  float width , float height_world){
    create_wall(b2Vec2(center_world.x - width/2 , center_world.y) , height_world , 90);
    create_wall(b2Vec2(center_world.x + width/2 , center_world.y) , height_world, 90);
    create_wall(b2Vec2(center_world.x , center_world.y - height_world/2) , width, 0);
    create_wall(b2Vec2(center_world.x , center_world.y + height_world/2) , width, 0);
}

void GameBuilder::create_small_platform(float x, float y, float angle) {
    create_platform(x, y, PLAT_SMALL, PLAT_HEIGHT , angle);
}

void GameBuilder::create_big_platform(float x, float y, float angle) {
    create_platform(x, y, PLAT_BIG, PLAT_HEIGHT , angle);
}

b2Body* GameBuilder::create_worm(float x, float y) {  // TODO: Create Class Worm
    b2BodyDef worm_def;
    worm_def.type = b2_dynamicBody;
    worm_def.position.Set(x, y);
    worm_def.linearDamping = 0.8f;
    b2Body* worm = world.CreateBody(&worm_def);
    b2PolygonShape worm_shape;
    worm_shape.SetAsBox(WORM_WIDTH / 2.0f, WORM_HEIGHT / 2.0f);
    b2FixtureDef worm_fixture;
    worm_fixture.density = 1;
    worm_fixture.shape = &worm_shape;
    worm_fixture.restitution = 0.2f;
    worm_fixture.friction = WORM_FRICTION;
    worm->CreateFixture(&worm_fixture);
    return worm;
}

b2Body* GameBuilder::create_provision_box_body(float x , float y){
    b2BodyDef box_def;
    box_def.type = b2_dynamicBody;
    box_def.position.Set(x, y);
    b2Body* box = world.CreateBody(&box_def);
    b2PolygonShape box_shape;
    box_shape.SetAsBox(1, 1);
    b2FixtureDef box_fixture;
    box_fixture.shape = &box_shape;
    box_fixture.density = 1;
    box_fixture.restitution = 0;
    box_fixture.friction = 2;
    box->CreateFixture(&box_fixture);
    return box;
}


void GameBuilder::create_platform_type(float x , float y, BeamType type){
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

b2Body* GameBuilder::create_projectile_body(float angle , float x , float y, float restitution, float density){
        b2BodyDef projectile_def;
        projectile_def.type = b2_dynamicBody;
        projectile_def.bullet = true;
        projectile_def.position.Set(x, y);
        projectile_def.angle = angle;
        b2Body* projectile = world.CreateBody(&projectile_def);

        b2CircleShape projectile_shape;
        projectile_shape.m_radius = 0.2;

        b2FixtureDef projectile_fixture;
        projectile_fixture.shape = &projectile_shape;
        projectile_fixture.density = density;
        projectile_fixture.restitution = restitution;
        projectile->CreateFixture(&projectile_fixture);
        return projectile;
}

b2Body* GameBuilder::create_fragment_body(b2Body* father_body , float angle){
    b2Vec2 pos = father_body->GetPosition();

    float xOffset = cos(angle) * father_body->GetFixtureList()->GetShape()->m_radius +0.3f;
    float yOffset = sin(angle) * father_body->GetFixtureList()->GetShape()->m_radius +0.3f;

    b2BodyDef fragment_def;
    fragment_def.type = b2_dynamicBody;
    fragment_def.bullet = true;
    fragment_def.position.Set(pos.x + xOffset, pos.y + yOffset);
    fragment_def.angle = angle;
    b2Body* fragment = world.CreateBody(&fragment_def);

    b2CircleShape fragment_shape;
    fragment_shape.m_radius = 0.2f;
    b2FixtureDef fragment_fixture;
    fragment_fixture.shape = &fragment_shape;
    fragment_fixture.density = 1;
    fragment_fixture.restitution = 0;
    fragment->CreateFixture(&fragment_fixture);

    return fragment;
}
