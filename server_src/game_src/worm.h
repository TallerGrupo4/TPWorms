#include <vector>

#include <box2d/box2d.h>

#include "../../common_src/constants.h"

#define START_LIFE 100
#define NO_WEAPON 0
#define NULL_STATE 0

#ifndef WORM_H
#define WORM_H

class Worm {
    b2Body* body;
    char id;
    int life;
    int weapon;  // TODO implement actual weapons
    int state;

public:
    Worm(char id, b2Body* body):
            body(body), id(id), life(START_LIFE), weapon(NO_WEAPON), state(NULL_STATE) {}

    void move(int direction) {
        body->SetLinearVelocity(b2Vec2(0, 0));
        float impulse = body->GetMass() * direction * WORM_SPEED;
        body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
    }

    WormSnapshot get_snapshot() {
        float pos_x = body->GetPosition().x;
        float pos_y = body->GetPosition().y;
        float angle = body->GetAngle();
        int direction = body->GetLinearVelocity().x > 0 ? 1 : -1;
        WormSnapshot snapshot(id, pos_x, pos_y, angle, life, direction, weapon, state);
        return snapshot;
    }
};

#endif  // WORM_H