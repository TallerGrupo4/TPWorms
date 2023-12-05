#include "tool_bat_callback.h"

float b2RayCastBat::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                                  float fraction) {
    body = fixture->GetBody();
    return fraction;
}

b2RayCastBat::~b2RayCastBat() {}
