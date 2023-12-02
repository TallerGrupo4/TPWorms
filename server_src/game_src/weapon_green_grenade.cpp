#include "weapon_green_grenade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define GREEN_GRENADE_DAMAGE ConfigSingleton::getInstance().get_green_grenade_damage()
#define GREEN_GRENADE_RADIUS ConfigSingleton::getInstance().get_green_grenade_radius()
#define GREEN_GRENADE_RESTITUTION ConfigSingleton::getInstance().get_green_grenade_restitution()
#define GREEN_GRENADE_DENSITY ConfigSingleton::getInstance().get_green_grenade_density()

GreenGrenade::GreenGrenade() : Weapon(GREEN_GRENADE, INF_AMMO , INF_AMMO , GREEN_GRENADE_DAMAGE, GREEN_GRENADE_RADIUS, 0  , EXPLOSIVE_TIMER, GreenGrenadeProj, false, true, true) {}

void GreenGrenade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, ProjectileManager& projectiles){
    std::shared_ptr<Projectile> projectile = create_projectile(worm, direction, angle, power, time, GREEN_GRENADE_RESTITUTION, GREEN_GRENADE_DENSITY);
    projectiles.add_projectile(projectile);
    shoot (b2Vec2(direction * cos(angle), sin(angle)), power, projectile->get_body());
}



GreenGrenade::~GreenGrenade(){}

