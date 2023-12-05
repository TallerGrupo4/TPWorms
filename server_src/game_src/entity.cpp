#include "entity.h"

#include <stdio.h>

Entity::Entity(b2Body* body, BodyType type): type(type), body(body) {}

b2Body* Entity::get_body() { return body; }

BodyType Entity::get_type() { return type; }

Entity::~Entity() {}
