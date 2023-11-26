#include "game_constants.h"
#include "../../common_src/constants.h"
#include "tool.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon: public Tool {
    protected:
    int damage ;
    int radius;
    int timer;
    int fragments;
    int fragment_damage;
    bool is_afected_by_wind;
    bool can_aim;
    bool has_potency;

    Weapon(uint8_t type , int ammo, int damage , int radius , int timer , int fragments , int fragment_damage , bool is_afected_by_wind , bool can_aim , bool has_potency) :
        Tool(type, ammo), damage(damage), radius(radius), timer(timer), fragments(fragments), fragment_damage(fragment_damage), is_afected_by_wind(is_afected_by_wind), can_aim(can_aim), has_potency(has_potency) {}

    

};


#endif // WEAPON_H
