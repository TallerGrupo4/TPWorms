#include "provisionBox.h"

ProvisionBox::ProvisionBox(b2Body* body, BoxType type, char id) : Entity(body, PROVISION_BOX), type(type), id(id), state(PICKED) {}

ProvisionBox::~ProvisionBox() {}

BoxType ProvisionBox::get_box_type() {
    return type;
}

void ProvisionBox::set_state(BoxState state) {
    this->state = state;
}

BoxState ProvisionBox::get_state() {
    return state;
}


