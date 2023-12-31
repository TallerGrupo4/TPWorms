#include "weapon_red_grenade.h"

#include <memory>

#include "../../common_src/constants.h"
#include "../config.h"

#define RED_GRENADE_DAMAGE ConfigSingleton::getInstance().get_red_grenade_damage()
#define RED_GRENADE_RADIUS ConfigSingleton::getInstance().get_red_grenade_radius()
#define RED_GRENADE_FRAGMENTS ConfigSingleton::getInstance().get_red_grenade_fragments()
#define RED_GRENADE_RESTITUTION ConfigSingleton::getInstance().get_red_grenade_restitution()
#define RED_GRENADE_DENSITY ConfigSingleton::getInstance().get_red_grenade_density()
#define RED_GRENADE_MAX_AMMO ConfigSingleton::getInstance().get_red_grenade_max_ammo()

RedGrenade::RedGrenade():
        Weapon(RED_GRENADE, RED_GRENADE_MAX_AMMO / 2, RED_GRENADE_MAX_AMMO, RED_GRENADE_DAMAGE,
               RED_GRENADE_RADIUS, RED_GRENADE_FRAGMENTS, EXPLOSIVE_TIMER, RedGrenadeProj, false,
               true, true) {}

bool RedGrenade::use(b2Body* worm, int direction, float angle, int time, int power, float x,
                     float y, ProjectileManager& projectiles) {
    std::shared_ptr<Projectile> projectile = create_projectile(
            worm, direction, angle, power, time, RED_GRENADE_RESTITUTION, RED_GRENADE_DENSITY);
    projectiles.add_projectile(projectile);
    shoot(b2Vec2(direction * cos(angle), sin(angle)), power, projectile->get_body());
    return true;
}

RedGrenade::~RedGrenade() {}
