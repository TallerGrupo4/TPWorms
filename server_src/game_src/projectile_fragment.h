#include "projectile.h"

class ProjectileFragment: public Projectile {
public:
    ProjectileFragment(b2Body* body, float angle);

    ~ProjectileFragment();
};
