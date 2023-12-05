#include "weapon_banana.h"

#include <memory>

#include "../../common_src/constants.h"
#include "../config.h"

#define BANANA_DAMAGE ConfigSingleton::getInstance().get_banana_damage()
#define BANANA_RADIUS ConfigSingleton::getInstance().get_banana_radius()
#define BANANA_RESTITUTION ConfigSingleton::getInstance().get_banana_restitution()
#define BANANA_DENSITY ConfigSingleton::getInstance().get_banana_density()
#define BANANA_MAX_AMMO ConfigSingleton::getInstance().get_banana_max_ammo()

Banana::Banana():
        Weapon(BANANA, BANANA_MAX_AMMO / 2, BANANA_MAX_AMMO, BANANA_DAMAGE, BANANA_RADIUS, 0,
               EXPLOSIVE_TIMER, BananaProj, false, true, true) {}

bool Banana::use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
                 ProjectileManager& projectiles) {
    std::shared_ptr<Projectile> projectile = create_projectile(worm, direction, angle, power, time,
                                                               BANANA_RESTITUTION, BANANA_DENSITY);
    projectiles.add_projectile(projectile);
    shoot(b2Vec2(direction * cos(angle), sin(angle)), power, projectile->get_body());
    return true;
}

Banana::~Banana() {}
