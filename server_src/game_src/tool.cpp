#include "tool.h"

Tool::Tool(uint8_t type, int ammo, bool can_aim) :
        type(type), ammo(ammo), has_scope(can_aim) {}

uint8_t Tool::get_type(){
    return type;
}

bool Tool::can_aim(){
    return has_scope;
}

