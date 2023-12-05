#ifndef MORTAR_H
#define MORTAR_H

#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"


class Mortar: public Weapon {

public:
    Mortar();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~Mortar();
};


#endif  // MORTAR_H
