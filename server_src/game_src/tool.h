#ifndef TOOL_H
#define TOOL_H

#include <unordered_set>
#include <memory>
#include "projectile.h"
#include <box2d/box2d.h>


class Tool {
    protected:
    uint8_t type;
    int ammo;
    bool has_scope;
    
    Tool(uint8_t type, int ammo, bool can_aim) :
        type(type), ammo(ammo), has_scope(can_aim) {}

    public:
    virtual void use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) = 0;

    uint8_t get_type(){
        return type;
    }

    int can_aim(){
        return has_scope;
    }
};

#endif // TOOL_H
