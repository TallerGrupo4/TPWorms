#include "weapon_bazooka.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define BAZOOKA_DAMAGE ConfigSingleton::getInstance().get_bazooka_damage()
#define BAZOOKA_RADIUS ConfigSingleton::getInstance().get_bazooka_radius()
#define BAZOOKA_RESTITUTION ConfigSingleton::getInstance().get_bazooka_misile_restitution()
#define BAZOOKA_DENSITY ConfigSingleton::getInstance().get_bazooka_misile_density()

Bazooka::Bazooka() : Weapon(BAZOOKA, -1 , -1 , BAZOOKA_DAMAGE, BAZOOKA_RADIUS, 0, EXPLOSIVE, BAZOOKA_PROJECTILE, true, true, true) {}

void Bazooka::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    Projectile* projectile = create_projectile(worm, direction, angle, power, 0, BAZOOKA_RESTITUTION, BAZOOKA_DENSITY);
    std::shared_ptr<Projectile> ptr(projectile);
    projectiles.insert(ptr);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Bazooka::~Bazooka(){}

