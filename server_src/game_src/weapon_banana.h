#ifndef BANANA_H
#define BANANA_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class Banana : public Weapon {

    public:
    Banana();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    Projectile* create_projectile(b2Body* worm, int direction, float angle , int power);

    ~Banana();

};



#endif  // BANANA_H
