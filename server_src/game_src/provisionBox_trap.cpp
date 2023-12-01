#include "provisionBox_trap.h"
#include "explosion.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()

TrapBox::TrapBox(b2Body* body, char id, int damage) : ProvisionBox(body, TRAP_BOX, id), damage(damage){}

void TrapBox::apply_effect(Worm* worm) {

    Explosion explosion(EXPLOSIVE , 0 , 0 , 2 , damage, EXPLOSION_POWER);
    explosion.apply_explosion(worm->get_body());
}

TrapBox::~TrapBox() {}

