#include "../../common_src/constants.h"
#include "worm.h"
#include <box2d/box2d.h>

#ifndef PROVISION_BOX_H
#define PROVISION_BOX_H

class ProvisionBox: public Entity {
    BoxType type;
    char id;
    BoxState state;

    public:

    ProvisionBox(b2Body* body, BoxType type, char id);

    ~ProvisionBox();

    BoxType get_box_type();

    BoxState get_state();

    void set_state(BoxState state);

    virtual void apply_effect(Worm* worm) = 0;

};

#endif // PROVISION_BOX_H