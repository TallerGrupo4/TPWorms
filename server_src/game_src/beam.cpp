#include "beam.h"

#include <box2d/box2d.h>

#include "game_constants.h"

Beam::Beam(b2Body* body): Entity(body, BEAM) {
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Beam::~Beam() {}
