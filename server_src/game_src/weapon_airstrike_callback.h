#include <box2d/box2d.h>
#include <list>

class b2RayCastStrike: public b2RayCastCallback{
    public:
    std::list<b2Body*> bodies;

    float ReportFixture(b2Fixture* fixture , const b2Vec2& point , const b2Vec2& normal , float fraction) override;

    ~b2RayCastStrike();
};
