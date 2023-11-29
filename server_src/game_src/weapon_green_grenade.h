#ifndef GREEN_GRENADE_H
#define GREEN_GRENADE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class GreenGrenade : public Weapon {

    public:
    GreenGrenade();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    ~GreenGrenade();

};



#endif  // GREEN_GRENADE_H
