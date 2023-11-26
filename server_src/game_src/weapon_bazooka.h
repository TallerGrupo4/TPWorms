#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>

#ifndef BAZOOKA_H
#define BAZOOKA_H


class Bazooka : public Weapon {

    public:
    Bazooka() : Weapon(BAZOOKA_TYPE, 1 , BAZOOKA_DAMAGE, BAZOOKA_RADIUS, 0 , 0 , 0, true, true, true) {}

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override {
        std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
        projectiles.insert(projectile);

        projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
    }

    b2Body* create_projectile_body(b2World* world, float angle , float x , float y) {
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
        projectile->CreateFixture(&projectile_fixture);
        return projectile;
    }

    Projectile* create_projectile(b2Body* worm, int direction, float angle , int power){
        float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
        float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

        b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y);
        Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

        return projectile;
    }

};

#endif // BAZOOKA_H
