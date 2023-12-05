#include "tool.h"

Tool::Tool(uint8_t type, int ammo, int max_ammo, bool can_aim):
        type(type), ammo(ammo), max_ammo(max_ammo), has_scope(can_aim) {}

uint8_t Tool::get_type() { return type; }

bool Tool::can_aim() { return has_scope; }

bool Tool::has_ammo() {
    if (ammo > 0 || ammo == INF_AMMO) {
        return true;
    }
    return false;
}

void Tool::add_ammo(int ammo) {
    if (this->ammo + ammo > max_ammo) {
        return;
    }
    this->ammo += ammo;
}

int Tool::get_ammo() { return ammo; }

Tool::~Tool() {}
