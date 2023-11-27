#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <box2d/box2d.h>
#include "explosion.h"
#include "memory"
#include "unordered_set"
#include "game_constants.h"
#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"


class Projectile {
    b2Body* body;
    int damage;
    int radius;
    int type;
    int explosion_type;
    int timer;
    int fragments;
    int fragment_damage;
    float angle;
    char state;

    public: 
        Projectile(b2Body* body, int damage, int radius, int type, int explosion_type, int timer, int fragments, int fragment_damage, float angle);

        ~Projectile();

        b2Body* get_body();

        int get_state();

        void set_state(char state);

        void decresease_timer(int tick);

        void explode(std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

        int get_type();

        int get_direction();

        float get_angle();

        int get_explosion_type();

        int get_timer();

        int get_fragments();

        int get_fragment_damage();

        ProjectileSnapshot get_snapshot();

};

#endif // PROJECTILE_H
