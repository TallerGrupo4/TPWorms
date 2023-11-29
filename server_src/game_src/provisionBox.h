#include "../../common_src/constants.h"
#include "worm.h"
#include <box2d/box2d.h>

class ProvisionBox {
    b2Body* body; 
    BoxType type;
    char id;
    BoxState state;

    public:

    ProvisionBox(b2Body* body, BoxType type, char id);

    ~ProvisionBox();

    virtual void apply_effect(Worm* worm) = 0;

};