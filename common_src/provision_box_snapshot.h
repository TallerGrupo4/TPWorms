#include "./constants.h"

#ifndef PROVISION_BOX_SNAPSHOT_H
#define PROVISION_BOX_SNAPSHOT_H

class ProvisionBoxSnapshot {
public:
    char type;
    float pos_x;
    float pos_y;
    char id;
    BoxType state;

    ProvisionBoxSnapshot(char type, float pos_x, float pos_y, char id, BoxType state):
            type(type), pos_x(pos_x), pos_y(pos_y), id(id), state(state) {};
};

#endif //PROVISION_BOX_SNAPSHOT_H
