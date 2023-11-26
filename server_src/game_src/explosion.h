#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <box2d/box2d.h>


class Explosion {
    protected:
    int type;
    int fragments;
    int fragment_damage;
    int radius;
    int damage;

    public:
    Explosion(int type, int fragments, int fragment_damage, int radius, int damage);
    
    void explode(b2Body* body);

    ~Explosion() {}

};

#endif // EXPLOTION_H
