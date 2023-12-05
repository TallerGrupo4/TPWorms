#include "provisionBox.h"

#define HEALTH_BOX_LIFE ConfigSingleton::getInstance().get_health_box_life()
#define TRAP_BOX_DAMAGE ConfigSingleton::getInstance().get_trap_box_damage()
#define TRAP_BOX_POWER ConfigSingleton::getInstance().get_trap_box_power()
#define TRAP_BOX_RADIUS ConfigSingleton::getInstance().get_trap_box_radius()
#define AMMO_BOX_AMMO ConfigSingleton::getInstance().get_ammo_box_ammo()

ProvisionBox::ProvisionBox(b2Body* body, BoxType type, char id):
        Entity(body, PROVISION_BOX), box_type(type), id(id), state(UNPICKED) {
    body->GetUserData().pointer = (uintptr_t)this;
}

ProvisionBox::~ProvisionBox() {}

BoxType ProvisionBox::get_box_type() { return box_type; }

void ProvisionBox::set_state(BoxState state) { this->state = state; }

BoxState ProvisionBox::get_state() { return state; }

ProvisionBoxSnapshot ProvisionBox::get_snapshot() {
    float x = this->body->GetPosition().x;
    float y = this->body->GetPosition().y;
    return ProvisionBoxSnapshot(box_type, x, y, id, state, 2, 2);
}


void ProvisionBox::apply_effect(Worm* worm) {
    TOOLS tool = (TOOLS)(rand() % 10);
    switch (box_type) {
        case HEALTH_BOX: {
            worm->add_health(HEALTH_BOX_LIFE);
            break;
        }
        case AMMO_BOX: {
            while (tool == BAZOOKA || tool == GREEN_GRENADE || tool == TELEPORTATION ||
                   tool == BASEBALL_BAT || tool == NO_TOOL) {
                tool = (TOOLS)(rand() % 10);
            }
            worm->add_ammo(AMMO_BOX_AMMO, tool);
            break;
        }
        default: {
            Explosion exp(EXPLOSIVE, 0, 0, TRAP_BOX_RADIUS, TRAP_BOX_DAMAGE, TRAP_BOX_POWER);
            exp.apply_explosion(body);
            break;
        }
    }
    state = PICKED;
}
