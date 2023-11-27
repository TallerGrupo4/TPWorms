#include "explosion.h"
#include <iostream>
#include "worm.h"
#include "explosion_callback.h"
#include "../config.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()



Explosion::Explosion(int type, int fragments, int fragment_damage, int radius, int damage) : type(type), fragments(fragments), fragment_damage(fragment_damage), radius(radius), damage(damage) {}

void Explosion::explode(b2Body* body , std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::unordered_set<b2Body*> bodies;
    for (int i = 0; i < 64; i++){
        float angle = (i/(float)64) * 360 * DEGTORAD;
        std::cout << "body GetPosition_x: " << body->GetPosition().x << " body GetPosition_y " << body->GetPosition().y << std::endl;
        b2Vec2 direction = b2Vec2(cos(angle), sin(angle));
        std::cout << "direction: " << direction.x << " " << direction.y << std::endl;
        b2Vec2 endPos = body->GetPosition() + radius * direction;
        std::cout << "Explosion endPos: " << endPos.x << " " << endPos.y << std::endl;
        printf("\n");
        b2RayCastExplosionCallback callback;
        // continue;
        std::cout << "IT BREAKS HERE IN EXPLOSION.CPP LINE 25!!!" << std::endl;
        body->GetWorld()->RayCast(&callback, body->GetPosition(), endPos);
        if (callback.body && bodies.find(callback.body) == bodies.end()){
            Worm* w = reinterpret_cast<Worm*>(static_cast<uintptr_t>(callback.body->GetUserData().pointer));
            if (w && w->get_type() == WORM){
                float explosion_distance = (callback.body->GetPosition() - body->GetPosition()).Length();
                w->apply_damage(damage * ((explosion_distance) / radius));
                callback.body -> ApplyLinearImpulse((EXPLOSION_POWER/explosion_distance) * direction, callback.body->GetWorldCenter(), true);
            }
            bodies.insert(callback.body);
        }
    }

    // TODO: fragment explosion
}


