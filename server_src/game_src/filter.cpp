#include "filter.h"
#include "worm.h"


    bool MyFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {
        b2Body *bodyA = fixtureA->GetBody();
        b2Body *bodyB = fixtureB->GetBody();

        if (bodyA->GetType() == b2_staticBody ||bodyB->GetType() == b2_staticBody){ return true; }

        Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
        Worm* wB = reinterpret_cast<Worm*>(bodyB->GetUserData().pointer);

        if (wA && wB && wA->get_type() == WORM && wB->get_type() == WORM){ return false; }

        return true;

    }

    MyFilter::~MyFilter(){}

