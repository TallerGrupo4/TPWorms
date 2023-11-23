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

class MyListener : public b2ContactListener{

    void execute_contact_jump(b2Body* bodyA , b2Body* bodyB){
        if (bodyA && bodyB && bodyA->GetUserData().pointer){
            WormData* wA = reinterpret_cast<WormData*>(bodyA->GetUserData().pointer);
            if (wA && wA->get_type() == WORM && bodyB->GetType() == b2_staticBody) {
                wA->add_contact();
                if (wA->get_state() == JUMPING || wA->get_state() == FALLING || wA->get_state() == BACKFLIPPING){
                    float y_diff = bodyA->GetPosition().y - wA->get_last_y();
                    if (y_diff < -FALL_DISTANCE_THRESHOLD){
                        int damage = abs(std::round(y_diff));
                        if (damage > FALL_DAMAGE_THRESHOLD){
                            wA->apply_damage(FALL_DAMAGE_THRESHOLD);
                        } else {wA->apply_damage(damage);}
                    }
                }
            }
        }
    }



    void BeginContact(b2Contact* contact) override {

        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        execute_contact_jump(bodyA, bodyB);
        execute_contact_jump(bodyB, bodyA);
    }

    void change_last_y(b2Body* bodyA , b2Body* bodyB){
        if (bodyA && bodyB && bodyA->GetUserData().pointer){
            WormData* wA = reinterpret_cast<WormData*>(bodyA->GetUserData().pointer);
            if (wA && bodyB->GetType() == b2_staticBody && wA->get_type() == WORM) {
                wA->remove_contact();
                wA->set_last_y(bodyA->GetPosition().y);
            }
        }
    }

    void EndContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        change_last_y(bodyA, bodyB);
        change_last_y(bodyB, bodyA);
    }
};



#endif //LISTENERS_H