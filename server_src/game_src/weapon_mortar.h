#ifndef MORTAR_H
#define MORTAR_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class Mortar : public Weapon {

    public:
    Mortar();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, ProjectileManager& projectiles) override;

    ~Mortar();

};



#endif  // MORTAR_H
