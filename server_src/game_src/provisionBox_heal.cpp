#include "provisionBox_heal.h"

HealBox::HealBox(b2Body* body, char id, int health) : ProvisionBox(body, HEALTH_BOX, id), health(health){}

void HealBox::apply_effect(Worm* worm) {
    worm->add_health(health);
}

HealBox::~HealBox() {}