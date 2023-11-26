#ifndef FILTER_H
#define FILTER_H

#include <box2d/box2d.h>
#include "worm.h"


class MyFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override {
        b2Body *bodyA = fixtureA->GetBody();
        b2Body *bodyB = fixtureB->GetBody();

        WormData* wA = reinterpret_cast<WormData*>(bodyA->GetUserData().pointer);
        WormData* wB = reinterpret_cast<WormData*>(bodyB->GetUserData().pointer);

        if (wA && wB && wA->get_type() == WORM && wB->get_type() == WORM){ return false; }

        return true;

    }
};

#endif //FILTER_H