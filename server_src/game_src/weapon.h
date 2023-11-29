#include "game_constants.h"
#include "../../common_src/constants.h"
#include "tool.h"

#ifndef WEAPON_H
#define WEAPON_H

class Weapon: public Tool {
    b2Body* create_projectile_body(b2World* world, float angle , float x , float y, float restitution, float density);

    protected:
    int damage ;
    int radius;
    int fragments;
    ExplosionType explosion_type;
    ProjectileTypes projectile_type;
    bool is_afected_by_wind;
    bool has_potency;

    Weapon(uint8_t type , int ammo,int max_ammo, int damage , int radius , int fragments , ExplosionType explosion_type , ProjectileTypes projectile_type , bool is_afected_by_wind , bool can_aim , bool has_potency);


    Projectile* create_projectile(b2Body* worm, int direction, float angle , int power, int timer, float restitution , float density);


};


#endif // WEAPON_H
