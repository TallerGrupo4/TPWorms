#include "weapon_bazooka.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define BAZOOKA_DAMAGE ConfigSingleton::getInstance().get_bazooka_damage()
#define BAZOOKA_RADIUS ConfigSingleton::getInstance().get_bazooka_radius()
#define BAZOOKA_RESTITUTION ConfigSingleton::getInstance().get_bazooka_misile_restitution()
#define BAZOOKA_DENSITY ConfigSingleton::getInstance().get_bazooka_misile_density()

Bazooka::Bazooka() : Weapon(BAZOOKA, -1 , -1 , BAZOOKA_DAMAGE, BAZOOKA_RADIUS, 0, EXPLOSIVE, BazookaProj, true, true, true) {}

void Bazooka::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, ProjectileManager& projectiles){
    std::shared_ptr<Projectile> ptr = create_projectile(worm, direction, angle, power, 0, BAZOOKA_RESTITUTION, BAZOOKA_DENSITY);
    projectiles.add_projectile(ptr);
    shoot (b2Vec2(direction * cos(angle), sin(angle)), power, ptr->get_body());
}



Bazooka::~Bazooka(){}

