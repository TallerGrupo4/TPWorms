#include <box2d/box2d.h>

#include "entity.h"

class Beam: public Entity {
public:
    explicit Beam(b2Body* body);
    ~Beam();
};
