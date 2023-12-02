#include "../../common_src/constants.h"
#include "worm.h"
#include <box2d/box2d.h>
#include "../../common_src/snapshot.h"


#ifndef PROVISION_BOX_H
#define PROVISION_BOX_H

class ProvisionBox: public Entity {
    protected:
    BoxType box_type;
    char id;
    BoxState state;

    public:

    ProvisionBox(b2Body* body, BoxType type, char id);

    ~ProvisionBox();

    BoxType get_box_type();

    BoxState get_state();

    void set_state(BoxState state);

    ProvisionBoxSnapshot get_snapshot();

    // virtual void apply_effect(Worm* worm) = 0;

    void apply_effect(Worm* worm);

};

#endif // PROVISION_BOX_H