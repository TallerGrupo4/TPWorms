#include "provisionBox_ammo.h"


AmmoBox::AmmoBox(b2Body* body,  char id, int ammo, TOOLS tool_type) : ProvisionBox(body, AMMO_BOX, id), ammo(ammo), weapon_type(tool_type) {}

void AmmoBox::apply_effect(Worm* worm) {
    worm->add_ammo(ammo, weapon_type);
}

AmmoBox::~AmmoBox() {}