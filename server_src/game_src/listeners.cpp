#include "listeners.h"
#include "game_constants.h"
#include "worm.h"
#include "explosion.h"
#include "provisionBox.h"



MyListener::MyListener(): b2ContactListener(){}

void MyListener::execute_explosive(b2Body* bodyB){
    if (bodyB->GetType () == b2_staticBody){
        return;
    }
    Projectile* pB = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    if (pB && pB->get_type() == PROJECITLE && bodyB->GetType() == b2_dynamicBody){
        pB->set_state(EXPLODED);
    }
}

void MyListener::execute_box_contact(b2Body* bodyA , b2Body* bodyB){
    if (bodyA->GetType () == b2_staticBody || bodyB->GetType () == b2_staticBody){
        return;
    }
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    ProvisionBox* pB = reinterpret_cast<ProvisionBox*>(bodyB->GetUserData().pointer);
    if (wA && pB && wA->get_type() == WORM && pB->get_body_type() == PROVISION_BOX ){
        pB->apply_effect(wA);
    }
}

void MyListener::execute_contact_jump(b2Body* bodyA , b2Body* bodyB){
    if (bodyA && bodyB){
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

    if (contact->IsTouching() == false){
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    if (bodyA == nullptr || bodyB == nullptr){
        return;
    }

    if (bodyA->GetType () == b2_staticBody && bodyB->GetType () == b2_staticBody){
        return;
    }


    execute_explosive(bodyA);
    execute_explosive(bodyB);

    execute_contact_jump(bodyA, bodyB);
    execute_contact_jump(bodyB, bodyA);

    execute_box_contact(bodyA, bodyB);
    execute_box_contact(bodyB, bodyA);
}

void MyListener::change_last_y(b2Body* bodyA , b2Body* bodyB){
    if (bodyA && bodyB){
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




