#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class RedGrenade: public Weapon {

public:
    RedGrenade();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~RedGrenade();
};


#endif  // RED_GRENADE_H
