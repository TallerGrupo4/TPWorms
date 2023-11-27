#include "explosion.h"
#include "worm.h"
#include "explosion_callback.h"
#include "../config.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()



Explosion::Explosion(int type, int fragments, int fragment_damage, int radius, int damage) : type(type), fragments(fragments), fragment_damage(fragment_damage), radius(radius), damage(damage) {}

void Explosion::explode(b2Body* body){
    std::unordered_set<b2Body*> bodies;
    for (int i = 0; i < 64; i++){
        float angle = (i/(float)64) * 360 * DEGTORAD;
        b2Vec2 direction = b2Vec2(cos(angle), sin(angle));
        b2Vec2 endPos = body->GetPosition() + radius * direction;

        b2RayCastExplosionCallback callback;
        body->GetWorld()->RayCast(&callback, body->GetPosition(), endPos);
        if (callback.body && bodies.find(callback.body) == bodies.end()){
            WormData* w = reinterpret_cast<WormData*>(static_cast<uintptr_t>(callback.body->GetUserData().pointer));
            if (w && w->get_type() == WORM){
                float explosion_distance = (callback.body->GetPosition() - body->GetPosition()).Length();
                w->apply_damage(damage * ((explosion_distance) / radius));
                callback.body -> ApplyLinearImpulse((EXPLOSION_POWER/explosion_distance) * direction, callback.body->GetWorldCenter(), true);
            }
            bodies.insert(callback.body);
        }
    }
}


