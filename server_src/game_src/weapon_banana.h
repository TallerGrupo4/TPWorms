#ifndef BANANA_H
#define BANANA_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class Banana : public Weapon {

    public:
    Banana();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, ProjectileManager& projectiles) override;

    ~Banana();

};



#endif  // BANANA_H
