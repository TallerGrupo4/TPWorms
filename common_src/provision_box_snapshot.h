#include "./constants.h"

#ifndef PROVISION_BOX_SNAPSHOT_H
#define PROVISION_BOX_SNAPSHOT_H

class ProvisionBoxSnapshot {
public:
    BoxType type;
    float pos_x;
    float pos_y;
    char id;
    BoxState state;
    float width;
    float height;

    ProvisionBoxSnapshot(BoxType type, float pos_x, float pos_y, char id, BoxState state, float width, float height):
            type(type), pos_x(pos_x), pos_y(pos_y), id(id), state(state), width(width), height(height) {};
};

#endif //PROVISION_BOX_SNAPSHOT_H
