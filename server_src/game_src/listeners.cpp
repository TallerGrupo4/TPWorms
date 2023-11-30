#include "listeners.h"
#include "game_constants.h"
#include "entity.h"
#include "worm.h"
#include "explosion.h"
#include "provisionBox.h"



MyListener::MyListener(): b2ContactListener(){}

void MyListener::handle_begin_contact(b2Body* bodyA , b2Body* bodyB){
    Entity* eA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* eB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (eA && eB){
        BodyType typeA = eA->get_type();
        BodyType typeB = eB->get_type();

        if (typeA == PROJECITLE){
            execute_explosive(bodyA);
        }

        if (typeA == WORM && typeB == PROVISION_BOX){
            execute_box_contact(bodyA, bodyB);
        }

        if (typeA == WORM && typeB == BEAM){
            execute_contact_jump(bodyA, bodyB);
        }
    }
}

void MyListener::handle_end_contact(b2Body* bodyA , b2Body* bodyB){
    Entity* eA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* eB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (eA && eB){
        BodyType typeA = eA->get_type();
        BodyType typeB = eB->get_type();

        if (typeA == WORM && typeB == BEAM){
            change_last_y(bodyA, bodyB);
        }
    }
}

void MyListener::execute_explosive(b2Body* bodyB){
    Projectile* pB = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    if (pB->get_explosion_type() == EXPLOSIVE){
        pB->set_state(EXPLODED);
    }
}

void MyListener::execute_box_contact(b2Body* bodyA , b2Body* bodyB){
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    ProvisionBox* pB = reinterpret_cast<ProvisionBox*>(bodyB->GetUserData().pointer);
    pB->apply_effect(wA);
}

void MyListener::execute_contact_jump(b2Body* bodyA , b2Body* bodyB){ 
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
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

void MyListener::BeginContact(b2Contact* contact){

    if (contact->IsTouching() == false){
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    handle_begin_contact(bodyA, bodyB);
    handle_begin_contact(bodyB, bodyA);
}

void MyListener::change_last_y(b2Body* bodyA , b2Body* bodyB){
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    wA->remove_contact();
    wA->set_last_y(bodyA->GetPosition().y);
}

void MyListener::EndContact(b2Contact* contact){
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    handle_end_contact(bodyA, bodyB);
    handle_end_contact(bodyB, bodyA);
}

MyListener::~MyListener() {}




