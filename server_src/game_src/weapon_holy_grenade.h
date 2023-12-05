#ifndef HOLY_GRENADE_H
#define HOLY_GRENADE_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class HolyGrenade: public Weapon {

public:
    HolyGrenade();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~HolyGrenade();
};


#endif  // HOLY_GRENADE_H
