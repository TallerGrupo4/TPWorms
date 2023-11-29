#include "weapon_holy_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define HOLY_GRANADE_DAMAGE ConfigSingleton::getInstance().get_holy_granade_damage()
#define HOLY_GRANADE_RADIUS ConfigSingleton::getInstance().get_holy_granade_radius()
#define HOLY_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_holy_granade_restitution()
#define HOLY_GRANADE_DENSITY ConfigSingleton::getInstance().get_holy_granade_density()
#define HOLY_GRANADE_MAX_AMMO ConfigSingleton::getInstance().get_holy_granade_max_ammo()

HolyGranade::HolyGranade() : Weapon(HOLY_GRANADE, HOLY_GRANADE_MAX_AMMO , HOLY_GRANADE_MAX_AMMO , HOLY_GRANADE_DAMAGE, HOLY_GRANADE_RADIUS, 0 , EXPLOSIVE_TIMER ,HolyGrenadeProj , true, true, true) {}

void HolyGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power, time , HOLY_GRANADE_RESTITUTION, HOLY_GRANADE_DENSITY));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}




HolyGranade::~HolyGranade() {}
