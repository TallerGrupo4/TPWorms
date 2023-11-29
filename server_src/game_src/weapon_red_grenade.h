#ifndef RED_GRENADE_H
#define RED_GRENADE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class RedGrenade : public Weapon {

    public:
    RedGrenade();

    // THIS WEAPON WILL ALSO HAVE FRAGMENTS!!!

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    ~RedGrenade();

};



#endif  // RED_GRENADE_H
