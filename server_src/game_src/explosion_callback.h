#ifndef EXPLOSION_CALLBACK_H
#define EXPLOSION_CALLBACK_H

#include <box2d/box2d.h>

class b2RayCastExplosionCallback : public b2RayCastCallback {
    friend class Explosion;
    b2Body* body = nullptr;

    float ReportFixture(b2Fixture* fixture , const b2Vec2& point , const b2Vec2& normal , float fraction);

    ~b2RayCastExplosionCallback();
};




#endif // EXPLOSION_CALLBACK_H