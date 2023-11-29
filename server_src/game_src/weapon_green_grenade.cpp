#include "weapon_green_grenade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define GREEN_GRENADE_DAMAGE ConfigSingleton::getInstance().get_green_grenade_damage()
#define GREEN_GRENADE_RADIUS ConfigSingleton::getInstance().get_green_grenade_radius()
#define GREEN_GRENADE_RESTITUTION ConfigSingleton::getInstance().get_green_grenade_restitution()
#define GREEN_GRENADE_DENSITY ConfigSingleton::getInstance().get_green_grenade_density()

GreenGrenade::GreenGrenade() : Weapon(GREEN_GRENADE, -1 , -1 , GREEN_GRENADE_DAMAGE, GREEN_GRENADE_RADIUS, 0  , EXPLOSIVE_TIMER, GreenGrenadeProj, false, true, true) {}

void GreenGrenade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile = create_projectile(worm, direction, angle, power, time, GREEN_GRENADE_RESTITUTION, GREEN_GRENADE_DENSITY);
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



GreenGrenade::~GreenGrenade(){}

