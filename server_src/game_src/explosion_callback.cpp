#include "explosion_callback.h"

float b2RayCastExplosionCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                                const b2Vec2& normal, float fraction) {
    bodies.push_back(fixture->GetBody());
    return 1;
}

b2RayCastExplosionCallback::~b2RayCastExplosionCallback() {}
