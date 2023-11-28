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
    bool has_potency;

    Weapon(uint8_t type , int ammo,int max_ammo, int damage , int radius , int timer , int fragments , int fragment_damage , bool is_afected_by_wind , bool can_aim , bool has_potency);

    b2Body* create_projectile_body(b2World* world, float angle , float x , float y, float restitution, float density);


};


#endif // WEAPON_H