#include "weapon_green_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define GREEN_GRANADE_DAMAGE ConfigSingleton::getInstance().get_green_granade_damage()
#define GREEN_GRANADE_RADIUS ConfigSingleton::getInstance().get_green_granade_radius()
#define GREEN_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_green_granade_restitution()
#define GREEN_GRANADE_DENSITY ConfigSingleton::getInstance().get_green_granade_density()

GreenGranade::GreenGranade() : Weapon(GREEN_GRANADE, -1 , -1 , GREEN_GRANADE_DAMAGE, GREEN_GRANADE_RADIUS, 0  , EXPLOSIVE_TIMER, GREEN_GRANADE_PROJECTILE, false, true, true) {}

void GreenGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power, time, GREEN_GRANADE_RESTITUTION, GREEN_GRANADE_DENSITY));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



GreenGranade::~GreenGranade(){}

