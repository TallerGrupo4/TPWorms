#include "provisionBox.h"

ProvisionBox::ProvisionBox(b2Body* body, BoxType type, char id) : Entity(body, PROVISION_BOX), box_type(type), id(id), state(UNPICKED) {
    body->GetUserData().pointer = (uintptr_t) this;
}

ProvisionBox::~ProvisionBox() {}

BoxType ProvisionBox::get_box_type() {
    return box_type;
}

void ProvisionBox::set_state(BoxState state) {
    this->state = state;
}

BoxState ProvisionBox::get_state() {
    return state;
}

ProvisionBoxSnapshot ProvisionBox::get_snapshot() {
    float x = this->body->GetPosition().x;
    float y = this->body->GetPosition().y;
    return ProvisionBoxSnapshot(box_type, x , y , id , state , 2 , 2);
}


void ProvisionBox::apply_effect(Worm* worm) {
    switch(box_type) {
        case HEALTH_BOX:
            worm->add_health(25);
            break;
        case AMMO_BOX:
            worm->add_ammo(1, MORTAR);
            break;
        default:
            Explosion exp(EXPLOSIVE , 0 , 0, 2 , 20, 20);
            exp.apply_explosion(body);
    }
    state = PICKED;
}