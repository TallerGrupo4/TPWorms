#ifndef LISTENERS_H
#define LISTENERS_H

#include <box2d/box2d.h>
#include <memory>
#include <unordered_set>
#include "projectile.h"


class MyListener : public b2ContactListener{
    std::unordered_set<std::shared_ptr<Projectile>>& projectiles;

    void EndContact(b2Contact* contact) override;

    void BeginContact(b2Contact* contact) override;

    void execute_explosive(b2Body* bodyB);

    void execute_contact_jump(b2Body* bodyA , b2Body* bodyB);

    void change_last_y(b2Body* bodyA , b2Body* bodyB);

    void execute_box_contact(b2Body* bodyA , b2Body* bodyB);

    public: MyListener(std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    ~MyListener();
};



#endif //LISTENERS_H