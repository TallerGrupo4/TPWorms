#include "explosion_callback.h"

float b2RayCastExplosionCallback::ReportFixture(b2Fixture* fixture , const b2Vec2& point , const b2Vec2& normal , float fraction){
    body = fixture->GetBody();
    return fraction;
}

b2RayCastExplosionCallback::~b2RayCastExplosionCallback(){}

