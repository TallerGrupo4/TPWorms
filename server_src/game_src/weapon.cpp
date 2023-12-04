#include "weapon.h"
#include "gamebuilder.h"

#define PROJECTILE_POTENCY ConfigSingleton::getInstance().get_projectile_potency()
   Weapon::Weapon(uint8_t type , int ammo,int max_ammo, int damage , int radius , int fragments , ExplosionType explosion_type , ProjectileTypes projectile_type , bool is_afected_by_wind , bool can_aim , bool has_potency) :
        Tool(type, ammo, max_ammo, can_aim), damage(damage), radius(radius), fragments(fragments), explosion_type(explosion_type), projectile_type(projectile_type), is_afected_by_wind(is_afected_by_wind), has_potency(has_potency) {}

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
        GameBuilder gamebuilder(*worm->GetWorld());
        b2Body* projectileBody = gamebuilder.create_projectile_body(angle, pos_x, pos_y, restitution, density);
        std::shared_ptr<Projectile> p = std::make_shared<Projectile>(projectileBody, damage, radius, projectile_type, explosion_type, timer, fragments, angle, is_afected_by_wind);

        return p;
    }

    void Weapon::shoot(b2Vec2 direction , int potency_percentage, b2Body* projectile){
        if (ammo > 0) {ammo--;}
        float impulse_x = direction.x * PROJECTILE_POTENCY *potency_percentage * 0.01;
        float impulse_y = direction.y * PROJECTILE_POTENCY* potency_percentage * 0.01;
        projectile->ApplyLinearImpulseToCenter(b2Vec2(impulse_x , impulse_y), true);
    }         


