#include "weapon.h"

   Weapon::Weapon(uint8_t type , int ammo, int damage , int radius , int timer , int fragments , int fragment_damage , bool is_afected_by_wind , bool can_aim , bool has_potency) :
        Tool(type, ammo, can_aim), damage(damage), radius(radius), timer(timer), fragments(fragments), fragment_damage(fragment_damage), is_afected_by_wind(is_afected_by_wind), has_potency(has_potency) {}

    b2Body* Weapon::create_projectile_body(b2World* world, float angle , float x , float y, float restitution) {
        b2BodyDef projectile_def;
        projectile_def.type = b2_dynamicBody;
        projectile_def.bullet = true;
        projectile_def.position.Set(x, y);
        projectile_def.angle = angle;
        b2Body* projectile = world->CreateBody(&projectile_def);

        b2CircleShape projectile_shape;
        projectile_shape.m_radius = 0.2;

        b2FixtureDef projectile_fixture;
        projectile_fixture.shape = &projectile_shape;
        projectile_fixture.density = 1;
        projectile_fixture.friction = restitution;
        projectile->CreateFixture(&projectile_fixture);
        return projectile;
    }


