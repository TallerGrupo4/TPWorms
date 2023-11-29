#include "weapon_red_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define RED_GRANADE_DAMAGE ConfigSingleton::getInstance().get_red_granade_damage()
#define RED_GRANADE_RADIUS ConfigSingleton::getInstance().get_red_granade_radius()
#define RED_GRANADE_FRAGMENTS ConfigSingleton::getInstance().get_red_granade_fragments()
#define RED_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_red_granade_restitution()
#define RED_GRANADE_DENSITY ConfigSingleton::getInstance().get_red_granade_density()
#define RED_GRANADE_MAX_AMMO ConfigSingleton::getInstance().get_red_granade_max_ammo()

RedGranade::RedGranade() : Weapon(RED_GRANADE, RED_GRANADE_MAX_AMMO , RED_GRANADE_MAX_AMMO , RED_GRANADE_DAMAGE, RED_GRANADE_RADIUS, RED_GRANADE_FRAGMENTS , EXPLOSIVE_TIMER, RedGrenadeProj, false, true, true) {}

void RedGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power, time, RED_GRANADE_RESTITUTION, RED_GRANADE_DENSITY ));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}

RedGranade::~RedGranade(){}

