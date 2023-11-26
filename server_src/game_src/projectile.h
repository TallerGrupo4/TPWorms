#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <box2d/box2d.h>
#include "explosion.h"


class ProjectileData {
    friend class Projectile;
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
    ProjectileData(int damage, int radius, int type, int explosion_type, int timer, int fragments, int fragment_damage, float angle, char state) :
        damage(damage), radius(radius), type(type), explosion_type(explosion_type), timer(timer), fragments(fragments), fragment_damage(fragment_damage), angle(angle), state(state) {}

    int get_type() {
        return PROJECITLE;
    }

    int get_explosion_type() {
        return explosion_type;
    }

    void set_state(char state) {
        this->state = state;
    }

    int get_state() {
        return state;
    }

    int get_damage() {
        return damage;
    }

    int get_radius() {
        return radius;
    }

    int get_timer() {
        return timer;
    }

    int get_fragments() {
        return fragments;
    }

    int get_fragment_damage() {
        return fragment_damage;
    }
};


class Projectile {
    b2Body* body;
    ProjectileData data;

    public: 
        Projectile(b2Body* body, int damage, int radius, int type, int explosion_type, int timer, int fragments, int fragment_damage, float angle) :
            body(body), data(damage, radius, type, explosion_type, timer, fragments, fragment_damage, angle, ALIVE) {
                body->GetUserData().pointer = (uintptr_t) &data;
            }

        ~Projectile() {}

        b2Body* get_body(){
            return body;
        }

        int get_state() {
            return data.get_state();
        }

        void decresease_timer(int tick) {
            if (data.timer > 0){
                data.timer -= tick;
            }
        }

        int get_timer() {
            return data.get_timer();
        }

        void explode() {
            data.set_state(EXPLODED);
            Explosion ex(data.get_explosion_type(), data.get_fragments(), data.get_fragment_damage(), data.get_radius(), data.get_damage());
            ex.explode(body);
        }

  
};

#endif // PROJECTILE_H
