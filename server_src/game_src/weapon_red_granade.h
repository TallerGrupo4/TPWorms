#ifndef RED_GRANADE_H
#define RED_GRANADE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class RedGranade : public Weapon {

    public:
    RedGranade();

    // THIS WEAPON WILL ALSO HAVE FRAGMENTS!!!

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    ~RedGranade();

};



#endif  // RED_GRANADE_H
