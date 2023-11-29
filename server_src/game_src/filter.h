#ifndef FILTER_H
#define FILTER_H

#include <box2d/box2d.h>


class MyFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

    public:
    ~MyFilter();
};

#endif //FILTER_H