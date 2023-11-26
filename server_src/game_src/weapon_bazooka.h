#include "weapon.h"
#include "projectile.h"
#include <box2d/box2d.h>

#ifndef BAZOOKA_H
#define BAZOOKA_H


class Bazooka : public Weapon {

    public:
    Bazooka();

    void use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;

    Projectile* create_projectile(b2Body* worm, int direction, float angle , int power);

};

#endif // BAZOOKA_H
