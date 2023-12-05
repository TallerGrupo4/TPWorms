#ifndef BANANA_H
#define BANANA_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class Banana: public Weapon {

public:
    Banana();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~Banana();
};


#endif  // BANANA_H
