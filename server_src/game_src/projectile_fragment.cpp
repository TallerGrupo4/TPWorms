#include "projectile_fragment.h"

#define FRAGMENT_DAMAGE ConfigSingleton::getInstance().get_fragment_damage()
#define FRAGMENT_RADIUS ConfigSingleton::getInstance().get_fragment_radius()

ProjectileFragment::ProjectileFragment(b2Body* body, float angle):
        Projectile(body, FRAGMENT_DAMAGE, FRAGMENT_RADIUS, FragmentProj, EXPLOSIVE, 0, 0, angle,
                   false) {}


ProjectileFragment::~ProjectileFragment() {}
