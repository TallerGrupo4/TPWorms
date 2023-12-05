#ifndef LISTENERS_H
#define LISTENERS_H

#include <memory>
#include <unordered_set>

#include <box2d/box2d.h>

#include "projectile.h"


class MyListener: public b2ContactListener {

    void EndContact(b2Contact* contact) override;

    void BeginContact(b2Contact* contact) override;

    void handle_begin_contact(b2Body* bodyA, b2Body* bodyB);

    void handle_end_contact(b2Body* bodyA, b2Body* bodyB);

    void execute_explosive(b2Body* bodyB);

    void execute_contact_jump(b2Body* bodyA, b2Body* bodyB);

    void change_last_y(b2Body* bodyA, b2Body* bodyB);

    void execute_box_contact(b2Body* bodyA, b2Body* bodyB);

public:
    MyListener();

    ~MyListener();
};


#endif  // LISTENERS_H
