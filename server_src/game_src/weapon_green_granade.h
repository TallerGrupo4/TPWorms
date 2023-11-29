#ifndef GREEN_GRANADE_H
#define GREEN_GRANADE_H

#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>


class GreenGranade : public Weapon {

    public:
    GreenGranade();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    ~GreenGranade();

};



#endif  // GREEN_GRANADE_H
