#include <box2d/box2d.h>

#include "game_constants.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    BodyType type;
    b2Body* body;

    Entity(b2Body* body, BodyType type);

public:
    b2Body* get_body();

    BodyType get_type();

    ~Entity();
};

#endif  // ENTITY_H
