#include "weapon_holy_grenade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define HOLY_GRENADE_DAMAGE ConfigSingleton::getInstance().get_holy_grenade_damage()
#define HOLY_GRENADE_RADIUS ConfigSingleton::getInstance().get_holy_grenade_radius()
#define HOLY_GRENADE_RESTITUTION ConfigSingleton::getInstance().get_holy_grenade_restitution()
#define HOLY_GRENADE_DENSITY ConfigSingleton::getInstance().get_holy_grenade_density()
#define HOLY_GRENADE_MAX_AMMO ConfigSingleton::getInstance().get_holy_grenade_max_ammo()

HolyGrenade::HolyGrenade() : Weapon(HOLY_GRENADE, HOLY_GRENADE_MAX_AMMO , HOLY_GRENADE_MAX_AMMO , HOLY_GRENADE_DAMAGE, HOLY_GRENADE_RADIUS, 0 , EXPLOSIVE_TIMER ,HolyGrenadeProj , true, true, true) {}

void HolyGrenade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power, time , HOLY_GRENADE_RESTITUTION, HOLY_GRENADE_DENSITY));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}




HolyGrenade::~HolyGrenade() {}
