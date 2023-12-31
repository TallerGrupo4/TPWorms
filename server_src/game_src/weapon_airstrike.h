#include <memory>

#include <box2d/box2d.h>

#include "../config.h"

#include "weapon.h"

#ifndef AIRSTRIKE_H
#define AIRSTRIKE_H

#define AIRSTRIKE_DAMAGE ConfigSingleton::getInstance().get_airstrike_damage()
#define AIRSTRIKE_RADIUS ConfigSingleton::getInstance().get_airstrike_radius()
#define AIRSTRIKE_MAX_AMMO ConfigSingleton::getInstance().get_airstrike_max_ammo()

class Airstrike: public Weapon {
    float get_roof_height(b2Body* worm);
    std::shared_ptr<Projectile> shoot_airstrike_projectile(b2Body* worm, float x, float y);

public:
    Airstrike();
    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;
    ~Airstrike();
};

#endif  // AIRSTRIKE_H
