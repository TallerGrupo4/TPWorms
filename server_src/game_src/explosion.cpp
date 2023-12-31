#include "explosion.h"

#include <iostream>

#include "../config.h"

#include "explosion_callback.h"
#include "gamebuilder.h"
#include "projectile_fragment.h"
#include "worm.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()


Explosion::Explosion(int type, int fragments, int fragment_damage, int radius, int damage,
                     int explosion_power):
        type(type),
        fragments(fragments),
        fragment_damage(fragment_damage),
        radius(radius),
        damage(damage),
        explosion_power(explosion_power) {}

void Explosion::sort_by_distance(std::list<b2Body*>& bodies, b2Body* body) {
    // This funcion sorts the bodies by distance to the center of the explosion so later we can
    // detect if the explosion was stopped in that direction by a static_body
    bodies.sort([body](b2Body* a, b2Body* b) {
        float distance_a = ((a->GetPosition()) - body->GetPosition()).Length();
        float distance_b = ((b->GetPosition()) - body->GetPosition()).Length();
        return distance_a < distance_b;
    });
}

void Explosion::apply_explosion(b2Body* body) {
    // This functions throws a raycast in 32 directions and applies damage and impulse to the
    // bodies that are hit by the raycast only if it wasn't stopped by a static_body
    std::unordered_set<b2Body*> bodies;
    b2World* world = body->GetWorld();
    for (int i = 0; i < 32; i++) {
        float angle = (i / (float)32) * 360 * DEGTORAD;
        b2Vec2 direction = b2Vec2(cos(angle), sin(angle));
        b2Vec2 endPos = body->GetPosition() + radius * direction;
        b2RayCastExplosionCallback callback;
        world->RayCast(&callback, body->GetPosition(), endPos);
        std::list<b2Body*> bodies_call = callback.bodies;
        sort_by_distance(bodies_call, body);
        for (b2Body* body_call: bodies_call) {
            if (body_call->GetType() == b2_staticBody) {
                break;
            }
            if (bodies.find(body_call) == bodies.end()) {
                Worm* w = reinterpret_cast<Worm*>(
                        static_cast<uintptr_t>(body_call->GetUserData().pointer));
                if (w) {
                    if (w->get_type() == WORM) {
                        float explosion_distance =
                                ((body_call->GetPosition()) - body->GetPosition()).Length() -
                                WORM_HEIGHT / 2.0f;
                        float act_damage = damage - (damage * (explosion_distance / float(radius)));
                        w->apply_damage(act_damage);
                        float impulse = explosion_power -
                                        (explosion_power * (explosion_distance / float(radius)));
                        body_call->ApplyLinearImpulseToCenter(impulse * direction, true);
                    }
                }
                bodies.insert(body_call);
            }
        }
    }
}


void Explosion::create_fragments(b2Body* body,
                                 std::unordered_set<std::shared_ptr<Projectile>>& projectiles) {
    for (int i = 0; i < fragments; i++) {
        float angle = (i / (float)fragments) * 360 * DEGTORAD;
        GameBuilder builder(*body->GetWorld());
        b2Body* fragment = builder.create_fragment_body(body, angle);
        std::shared_ptr<Projectile> ptr(new ProjectileFragment(fragment, angle));
        projectiles.insert(ptr);
        float impulse_x = 0.5f * cos(angle);
        float impulse_y = 0.5f * sin(angle);
        fragment->ApplyLinearImpulseToCenter(b2Vec2(impulse_x, impulse_y), true);
    }
}

void Explosion::explode(b2Body* body,
                        std::unordered_set<std::shared_ptr<Projectile>>& projectiles) {
    apply_explosion(body);
    if (fragments > 0) {
        create_fragments(body, projectiles);
    }
}

Explosion::~Explosion() {}
