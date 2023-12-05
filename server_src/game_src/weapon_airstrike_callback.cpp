#include "weapon_airstrike_callback.h"

#include <memory>
#include <vector>

float b2RayCastStrike::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                                     float fraction) {
    bodies.push_back(fixture->GetBody());
    return 1;
}

b2RayCastStrike::~b2RayCastStrike() {}
