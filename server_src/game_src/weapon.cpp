#include "weapon.h"
#include "gamebuilder.h"


   Weapon::Weapon(uint8_t type , int ammo,int max_ammo, int damage , int radius , int fragments , ExplosionType explosion_type , ProjectileTypes projectile_type , bool is_afected_by_wind , bool can_aim , bool has_potency) :
        Tool(type, ammo, can_aim, max_ammo), damage(damage), radius(radius), fragments(fragments), explosion_type(explosion_type), projectile_type(projectile_type), is_afected_by_wind(is_afected_by_wind), has_potency(has_potency) {}

    b2Body* Weapon::create_projectile_body(b2World* world, float angle , float x , float y, float restitution, float density) {
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
        projectile_fixture.density = density;
        projectile_fixture.friction = restitution;
        projectile->CreateFixture(&projectile_fixture);
        return projectile;
    }

    std::shared_ptr<Projectile> Weapon::create_projectile(b2Body* worm, int direction, float angle , int power , int timer , float restitution , float density) {
        float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
        float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;
        b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y, restitution, density);
        // GameBuilder gamebuilder(*worm->GetWorld());
        // b2Body* projectileBody = gamebuilder.create_projectile_body(angle, pos_x, pos_y, restitution, density);
        std::shared_ptr<Projectile> p = std::make_shared<Projectile>(projectileBody, damage, radius, projectile_type, explosion_type, timer, fragments, angle);

        return p;
    }
        // Projectile(b2Body* body, int damage, int radius, ProjectileTypes type, ExplosionType explosion_type, int timer, int fragments, float angle);


