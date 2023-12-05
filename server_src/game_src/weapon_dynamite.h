#ifndef DYNAMITE_H
#define DYNAMITE_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class Dynamite: public Weapon {

public:
    Dynamite();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~Dynamite();
};


#endif  // DYNAMITE_H
