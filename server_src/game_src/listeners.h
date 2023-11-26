#include <box2d/box2d.h>
#include <memory>
#include <unordered_set>
#include "explosion.h"

#include "game_constants.h"
#include "worm.h"
// #include "projectiles.h"

#ifndef LISTENERS_H
#define LISTENERS_H



class MyListener : public b2ContactListener{

    void execute_explosive(b2Body* bodyB){
        ProjectileData* pB = reinterpret_cast<ProjectileData*>(bodyB->GetUserData().pointer);
        if (pB && pB->get_type() == PROJECITLE){
            if (pB->get_explosion_type() == EXPLOSIVE){
                pB->set_state(EXPLODED);
                Explosion explosion(pB->get_explosion_type(), pB->get_fragments(), pB->get_fragment_damage(), pB->get_radius(), pB->get_damage(), 0);
                explosion.explode(bodyB);
            }
            // if (pB->get_explosion_type() == EXPLOSIVE_FRAGMENTS_IMPACT){
            //     explode_fragments(bodyB, 4, pB->get_damage());
            //     pB->set_state(DEAD);
            // }
        }
        


    }

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

        execute_explosive(bodyA);
        execute_explosive(bodyB);
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