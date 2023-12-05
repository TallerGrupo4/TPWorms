#include "filter.h"

#include "worm.h"


bool MyFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    Entity* eA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* eB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (eA->get_type() == BEAM && eB->get_type() == BEAM) {
        return false;
    }
    if (eA->get_type() == WORM && eB->get_type() == WORM) {
        return false;
    }
    if (eA->get_type() == PROJECITLE && eB->get_type() == PROJECITLE) {
        return false;
    }
    if (eA->get_type() == PROJECITLE && eB->get_type() == PROVISION_BOX) {
        return false;
    }
    if (eA->get_type() == PROVISION_BOX && eB->get_type() == PROJECITLE) {
        return false;
    }
    return true;
}

MyFilter::~MyFilter() {}
