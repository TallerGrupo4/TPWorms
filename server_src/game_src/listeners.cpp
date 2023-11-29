#include "listeners.h"
#include "game_constants.h"
#include "worm.h"
#include "explosion.h"



MyListener::MyListener(std::unordered_set<std::shared_ptr<Projectile>>& projectiles) : b2ContactListener() , projectiles(projectiles) {}


void MyListener::execute_explosive(b2Body* bodyB){
    Projectile* pB = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    if (pB && pB->get_type() == PROJECITLE){
        if (pB->get_explosion_type() == EXPLOSIVE){
            pB->explode(projectiles);
        }
    }
}

void MyListener::execute_contact_jump(b2Body* bodyA , b2Body* bodyB){
    if (bodyA && bodyB && bodyA->GetUserData().pointer){
        Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
        if (wA && wA->get_type() == WORM && bodyB->GetType() == b2_staticBody) {
            wA->add_contact();
            if (wA->get_state() == JUMPING || wA->get_state() == FALLING || wA->get_state() == BACKFLIPPING){
                bodyA->SetLinearVelocity(b2Vec2_zero);
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

void MyListener::BeginContact(b2Contact* contact){

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    execute_contact_jump(bodyA, bodyB);
    execute_contact_jump(bodyB, bodyA);

    execute_explosive(bodyA);
    execute_explosive(bodyB);
}

void MyListener::change_last_y(b2Body* bodyA , b2Body* bodyB){
    if (bodyA && bodyB && bodyA->GetUserData().pointer){
        Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
        if (wA && bodyB->GetType() == b2_staticBody && wA->get_type() == WORM) {
            wA->remove_contact();
            wA->set_last_y(bodyA->GetPosition().y);
        }
    }
}

void MyListener::EndContact(b2Contact* contact){
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    change_last_y(bodyA, bodyB);
    change_last_y(bodyB, bodyA);
}

MyListener::~MyListener() {}




