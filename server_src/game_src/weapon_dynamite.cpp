#include "weapon_dynamite.h"

#include <memory>

#include "../../common_src/constants.h"
#include "../config.h"

#define DYNAMITE_DAMAGE ConfigSingleton::getInstance().get_dynamite_damage()
#define DYNAMITE_RADIUS ConfigSingleton::getInstance().get_dynamite_radius()
#define DYNAMITE_RESTITUTION ConfigSingleton::getInstance().get_dynamite_restitution()
#define DYNAMITE_DENSITY ConfigSingleton::getInstance().get_dynamite_density()
#define DYNAMITE_MAX_AMMO ConfigSingleton::getInstance().get_dynamite_max_ammo()


Dynamite::Dynamite():
        Weapon(DYNAMITE, DYNAMITE_MAX_AMMO / 2, DYNAMITE_MAX_AMMO, DYNAMITE_DAMAGE, DYNAMITE_RADIUS,
               0, EXPLOSIVE_TIMER, DynamiteProj, false, false, false) {}

bool Dynamite::use(b2Body* worm, int direction, float angle, int time, int power, float x, float y,
                   ProjectileManager& projectiles) {
    std::shared_ptr<Projectile> projectile =
            create_projectile(worm, direction, 0, 0, time, DYNAMITE_RESTITUTION, DYNAMITE_DENSITY);
    projectiles.add_projectile(projectile);
    return true;
}


Dynamite::~Dynamite() {}
