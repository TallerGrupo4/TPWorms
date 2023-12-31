#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <list>
#include <memory>
#include <unordered_set>

#include <box2d/box2d.h>
class Projectile;


class Explosion {
protected:
    int type;
    int fragments;
    int fragment_damage;
    int radius;
    int damage;
    int explosion_power;


    void create_fragments(b2Body* body,
                          std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

public:
    Explosion(int type, int fragments, int fragment_damage, int radius, int damage,
              int explosion_power);

    void explode(b2Body* body, std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    void apply_explosion(b2Body* body);

    void sort_by_distance(std::list<b2Body*>& bodies, b2Body* body);


    ~Explosion();
};

#endif  // EXPLOTION_H
