#include <vector>

#include <box2d/box2d.h>

#include "../../common_src/constants.h"

#ifndef WORM_H
#define WORM_H

class WormNotFound: public std::exception {
    const char* what() const noexcept override {
        return "The worm body is a null pointer";
    }
};

#define START_LIFE 100


class Worm {
    friend class Game;
    b2Body* body;
    char id;
    int life;
    int weapon;  // TODO implement actual weapons
    int state;

public:
    Worm(char id, b2Body* body):
            body(body), id(id), life(START_LIFE), weapon(NO_WEAPON), state(STILL) {}

    void move(int direction) {
        body->SetLinearVelocity(b2Vec2(0, 0));
        float impulse = body->GetMass() * direction * WORM_SPEED;
        body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
        state = MOVING;
    }

    WormSnapshot get_snapshot() {
        if (body == nullptr){throw WormNotFound();}
        float pos_x = body->GetPosition().x;
        float pos_y = body->GetPosition().y;
        float angle = body->GetAngle();
        int direction = body->GetLinearVelocity().x > 0 ? 1 : -1;
        WormSnapshot snapshot(id, pos_x, pos_y, angle, 100, 100, direction, weapon, state);
        return snapshot;
    }

    const char get_id() const {
        return id;
    }
};

#endif  // WORM_H
