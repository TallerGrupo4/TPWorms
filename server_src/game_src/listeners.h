#include <box2d/box2d.h>
#include <memory>
#include <unordered_set>

#include "game_constants.h"
#include "worm.h"
// #include "projectiles.h"

#ifndef LISTENERS_H
#define LISTENERS_H

// class b2RayCastExplosionCallback : public b2RayCastCallback {
//     friend class ProjectileListener;
//     b2Body* body;

//     float ReportFixture(b2Fixture* fixture , const b2Vec2& point , const b2Vec2& normal , float fraction){
//         body = fixture->GetBody();
//         return fraction;
//     }
// };

// class ProjectileListener: public b2ContactListener{
//     void execute_contact(b2Body* bodyA , b2Body* bodyB){
//         WormData* wA = reinterpret_cast<WormData*>(static_cast<uintptr_t>(bodyA->GetUserData().pointer));
//         ProjectileData* pB = reinterpret_cast<ProjectileData*>(static_cast<uintptr_t>(bodyB->GetUserData().pointer));
//          if ( pB ) {
//             if (pB->explosion_type == EXPLOSIVE){
//                 explode(bodyB, 4, pB->damage);
//                 pB->alive = false;
//             }
//             if (pB->explosion_type == EXPLOSIVE_TIMER){
//                 if (pB->timer == 0){
//                     explode(bodyB, 4, pB->damage);
//                     pB->alive = false;
//                 } 
//             } 
//             // if (pB->explosion_type == EXPLOSIVE_FRAGMENTS_IMPACT){
//             //     explode_fragments(bodyB, 4, pB->damage);
//             //     pB->alive = false;
//             // }
//             // if (pB->explosion_type == EXPLOSIVE_FRAGMENTS_TIMER){
//             //     if (pB->timer == 0){
//             //         explode_fragments(bodyB, 4, pB->damage);
//             //         pB->alive = false;
//             //     } 
//             // }
//         }
//     }

//     void explode(b2Body* body , float radius, float damage){
//         std::unordered_set<b2Body*> bodies;
//         for (int i = 0; i < 64; i++){
//             float angle = (i/(float)64) * 360 * DEGTORAD;
//             b2Vec2 direction = b2Vec2(cos(angle), sin(angle));
//             b2Vec2 endPos = body->GetPosition() + radius * direction;

//             b2RayCastExplosionCallback callback;
//             body->GetWorld()->RayCast(&callback, body->GetPosition(), endPos);
//             if (callback.body && bodies.find(callback.body) == bodies.end()){
//                 WormData* w = reinterpret_cast<WormData*>(static_cast<uintptr_t>(callback.body->GetUserData().pointer));
//                 if (w && w->type == WORM){
//                     w->life -= damage * ((callback.body->GetPosition() - body->GetPosition()).Length() / radius);
//                     // w->life -= damage;
//                     callback.body -> ApplyLinearImpulse(10 * direction, callback.body->GetWorldCenter(), true);
//                 }
//                 bodies.insert(callback.body);
//             }
//         }
//     }

//     void BeginContact(b2Contact* contact) override {
//         b2Fixture* fixtureA = contact->GetFixtureA();
//         b2Fixture* fixtureB = contact->GetFixtureB();

//         b2Body* bodyA = fixtureA->GetBody();
//         b2Body* bodyB = fixtureB->GetBody();
//         execute_contact(bodyA, bodyB);
//         execute_contact(bodyB, bodyA);
//     }
// };

class JumpListener : public b2ContactListener{

    void execute_contact(b2Body* bodyA , b2Body* bodyB){
        WormData* wA = reinterpret_cast<WormData*>(static_cast<uintptr_t>(bodyA->GetUserData().pointer));
        if (wA && bodyB->GetType() == b2_staticBody) {
            if (wA->get_state() == FALLING) {
                wA->set_state(STILL);
                bodyA->SetLinearVelocity(b2Vec2(0, 0));
            }
        }
    }

    void BeginContact(b2Contact* contact) override {

        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        execute_contact(bodyA, bodyB);
        execute_contact(bodyB, bodyA);
    }
};



#endif //LISTENERS_H