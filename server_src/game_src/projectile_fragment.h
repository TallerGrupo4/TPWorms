#include "projectile.h"

class ProjectileFragment : public Projectile {
    public:

    ProjectileFragment(b2Body* body , float angle);

    b2Body* createFragmentBody(b2Body* fathers_body, float angle);

    ~ProjectileFragment();

};