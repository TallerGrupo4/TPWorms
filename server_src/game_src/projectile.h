#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <box2d/box2d.h>

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"

#include "entity.h"
#include "explosion.h"
#include "game_constants.h"
#include "memory"
#include "unordered_set"


class Projectile: public Entity {
    int damage;
    int radius;
    ProjectileTypes projectile_type;
    ExplosionType explosion_type;
    float radius_body_size;
    int timer;
    int fragments;
    float angle;
    char state;
    char id;
    bool affected_by_wind;

public:
    Projectile(b2Body* body, int damage, int radius, ProjectileTypes type,
               ExplosionType explosion_type, int timer, int fragments, float angle,
               bool affected_by_wind);

    ~Projectile();

    int get_state();

    void set_state(char state);

    void decresease_timer(int tick);

    void explode(std::unordered_set<std::shared_ptr<Projectile>>& projectiles);

    int get_direction();

    float get_angle();

    ExplosionType get_explosion_type();

    void set_angle(float angle);

    int get_timer();

    int get_fragments();

    ProjectileTypes get_projectile_type();

    int get_fragment_damage();

    bool is_affected_by_wind();

    void set_id(char id);

    char get_id();

    ProjectileSnapshot get_snapshot();
};

#endif  // PROJECTILE_H
