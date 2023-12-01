#ifndef TOOL_H
#define TOOL_H

#include <unordered_set>
#include <memory>
#include <box2d/box2d.h>
#include "projectile_manager.h"

class Tool {
    protected:
    uint8_t type;
    int ammo;
    int max_ammo;
    bool has_scope;
    
    Tool(uint8_t type, int ammo ,int max_ammo, bool can_aim);

    public:
    virtual void use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, ProjectileManager& projectiles) = 0;

    uint8_t get_type();

    bool can_aim();

    void add_ammo(int ammo);

    int get_ammo();

    ~Tool();
};

#endif // TOOL_H
