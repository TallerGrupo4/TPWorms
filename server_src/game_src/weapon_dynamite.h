#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class Dynamite : public Weapon {

    public:
    Dynamite();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    Projectile* create_projectile(b2Body* worm, int direction, float angle , int power);

    ~Dynamite();

};



#endif  // DYNAMITE_H
