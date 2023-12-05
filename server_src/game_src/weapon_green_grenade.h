#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class GreenGrenade: public Weapon {

public:
    GreenGrenade();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~GreenGrenade();
};


#endif  // GREEN_GRENADE_H
