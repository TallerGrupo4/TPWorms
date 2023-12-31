#include <box2d/box2d.h>

#include "projectile.h"
#include "weapon.h"

#ifndef BAZOOKA_H
#define BAZOOKA_H


class Bazooka: public Weapon {

public:
    Bazooka();

    bool use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
             ProjectileManager& projectiles) override;

    ~Bazooka();
};

#endif  // BAZOOKA_H
