#include <box2d/box2d.h>

class b2RayCastBat: public b2RayCastCallback {
    friend class Bat;
    b2Body* body = nullptr;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                        float fraction) override;

    ~b2RayCastBat();
};
