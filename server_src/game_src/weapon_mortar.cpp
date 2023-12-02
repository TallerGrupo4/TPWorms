#include "weapon_mortar.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define MORTAR_DAMAGE ConfigSingleton::getInstance().get_mortar_damage()
#define MORTAR_RADIUS ConfigSingleton::getInstance().get_mortar_radius()
#define MORTAR_RESTITUTION ConfigSingleton::getInstance().get_mortar_misile_restitution()
#define MORTAR_DENSITY ConfigSingleton::getInstance().get_mortar_misile_density()
#define MORTAR_MAX_AMMO ConfigSingleton::getInstance().get_mortar_max_ammo()
#define MORTAR_FRAGMENTS ConfigSingleton::getInstance().get_mortar_fragments()

Mortar::Mortar() : Weapon(MORTAR, MORTAR_MAX_AMMO/2 , MORTAR_MAX_AMMO , MORTAR_DAMAGE, MORTAR_RADIUS , MORTAR_FRAGMENTS , EXPLOSIVE, MortarProj ,  true, true, true) {}

void Mortar::use(b2Body* worm, int direction, float angle , int timer,  int power , float x , float y, ProjectileManager& projectiles){
    std::shared_ptr<Projectile> ptr = create_projectile(worm, direction, angle, power, 0, MORTAR_RESTITUTION, MORTAR_DENSITY);
    projectiles.add_projectile(ptr);
    shoot (b2Vec2(direction * cos(angle), sin(angle)), power, ptr->get_body());
}




Mortar::~Mortar(){}

