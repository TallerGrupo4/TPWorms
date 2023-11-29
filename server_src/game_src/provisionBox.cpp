#include "provisionBox.h"

ProvisionBox::ProvisionBox(b2Body* body, BoxType type, char id) : body(body), type(type), id(id), state(PICKED) {}

ProvisionBox::~ProvisionBox() {}

BodyType ProvisionBox::get_body_type(){
    return body_type;
}