#include <box2d/box2d.h>
#include "weapon.h"
#include "../config.h"

#ifndef AIRSTRIKE_H
#define AIRSTRIKE_H

#define AIRSTRIKE_DAMAGE ConfigSingleton::getInstance().get_airstrike_damage()
#define AIRSTRIKE_RADIUS ConfigSingleton::getInstance().get_airstrike_radius()
#define AIRSTRIKE_MAX_AMMO ConfigSingleton::getInstance().get_airstrike_max_ammo()

class Airstrike: public Weapon {
    float get_roof_height(b2Body* worm);
    Projectile* shoot_airstrike_projectile(b2Body* worm, float x , float y);

    public:
    Airstrike();
    void use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;
    ~Airstrike();

};

#endif  // AIRSTRIKE_H
