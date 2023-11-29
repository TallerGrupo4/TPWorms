#ifndef HOLY_GRENADE_H
#define HOLY_GRENADE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class HolyGrenade : public Weapon {

    public:
    HolyGrenade();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    ~HolyGrenade();

};



#endif  // HOLY_GRENADE_H