#include <box2d/box2d.h>
#include "entity.h"

class Beam: public Entity {
    public: 
    Beam(b2Body* body);
    ~Beam();
};

