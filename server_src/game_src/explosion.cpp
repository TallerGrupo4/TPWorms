#include "explosion.h"
#include <iostream>
#include "worm.h"
#include "explosion_callback.h"
#include "../config.h"
#include "projectile_fragment.h"
#include "gamebuilder.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()



Explosion::Explosion(int type, int fragments, int fragment_damage, int radius, int damage) : type(type), fragments(fragments), fragment_damage(fragment_damage), radius(radius), damage(damage) {}

void Explosion::apply_explosion(b2Body* body){
    std::unordered_set<b2Body*> bodies;
    b2World* world = body->GetWorld();
    for (int i = 0; i < 32; i++){
        float angle = (i/(float)32) * 360 * DEGTORAD;
        b2Vec2 direction = b2Vec2(cos(angle), sin(angle));
        b2Vec2 endPos = body->GetPosition() + radius * direction;
        b2RayCastExplosionCallback callback;
        world->RayCast(&callback, body->GetPosition(), endPos);
        b2Body* body_call = callback.body;
        if (body_call != nullptr){
            if (!bodies.empty() && bodies.find(body_call) != bodies.end()){
                continue;
            }
            if (body_call->GetType() == b2_staticBody){
                bodies.insert(body_call);
                continue;
            }
            Worm* w = reinterpret_cast<Worm*>(static_cast<uintptr_t>(body_call->GetUserData().pointer));
            if (w) {
                if (w->get_type() == WORM){
                    float explosion_distance = (body_call->GetPosition() - body->GetPosition()).Length();
                    w->apply_damage(damage * ((explosion_distance) / radius));
                    body_call -> ApplyLinearImpulseToCenter(EXPLOSION_POWER *(explosion_distance/radius) * direction, true);
                }
            }
            bodies.insert(body_call);
        }
    }

}

void Explosion::create_fragments(b2Body* body , std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    for (int i =0 ; i < fragments; i++){
        float angle = (i/(float)fragments) * 360 * DEGTORAD;
        GameBuilder builder(*body->GetWorld());
        b2Body* fragment = builder.create_fragment_body(body , angle);
        std::shared_ptr<Projectile> ptr(new ProjectileFragment(fragment, angle));
        projectiles.insert(ptr);
        fragment->ApplyLinearImpulseToCenter(b2Vec2(cos(angle) * EXPLOSION_POWER, sin(angle) * EXPLOSION_POWER), true);
    }
}

void Explosion::explode(b2Body* body , std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    apply_explosion(body);
    if (fragments > 0){
        create_fragments(body, projectiles);
    }
    
}

Explosion::~Explosion(){}