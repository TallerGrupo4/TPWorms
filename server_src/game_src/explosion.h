#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <box2d/box2d.h>
#include <unordered_set>
#include <memory>
class Projectile;


class Explosion {
    protected:
    int type;
    int fragments;
    int fragment_damage;
    int radius;
    int damage;

    void create_fragments(b2Body* body, std::unordered_set<std::shared_ptr<Projectile>>& projectiles);
    
    public:
    Explosion(int type, int fragments, int fragment_damage, int radius, int damage);
    
    void explode(b2Body* body, std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    void apply_explosion(b2Body* body);



    ~Explosion() {}

};

#endif // EXPLOTION_H
