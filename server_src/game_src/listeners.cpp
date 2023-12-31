#include "listeners.h"

#include "entity.h"
#include "explosion.h"
#include "game_constants.h"
#include "provisionBox.h"
#include "worm.h"


MyListener::MyListener(): b2ContactListener() {}

void MyListener::handle_begin_contact(b2Body* bodyA, b2Body* bodyB) {
    // This function handles the begin contact between two bodies
    // and executes the corresponding action depending on the body type
    // We need to cast the body's user data to an Entity* to get the type
    // Each entity in the game has a type that is defined constant.h that shares with the client
    Entity* eA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* eB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (eA && eB) {
        BodyType typeA = eA->get_type();
        BodyType typeB = eB->get_type();


        if (typeA == PROJECITLE) {
            execute_explosive(bodyA);
        }

        if (typeA == WORM && typeB == PROVISION_BOX) {
            execute_box_contact(bodyA, bodyB);
        }

        if (typeA == WORM && typeB == BEAM) {
            execute_contact_jump(bodyA, bodyB);
        }
    }
}

void MyListener::handle_end_contact(b2Body* bodyA, b2Body* bodyB) {
    // same logic as handle_begin_contact
    Entity* eA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* eB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (eA && eB) {
        BodyType typeA = eA->get_type();
        BodyType typeB = eB->get_type();

        if (typeA == WORM && typeB == BEAM) {
            change_last_y(bodyA, bodyB);
        }
    }
}

void MyListener::execute_explosive(b2Body* bodyB) {
    Projectile* pB = reinterpret_cast<Projectile*>(bodyB->GetUserData().pointer);
    if (pB->get_explosion_type() == EXPLOSIVE) {
        pB->set_state(EXPLODED);
    }
}

void MyListener::execute_box_contact(b2Body* bodyA, b2Body* bodyB) {
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    ProvisionBox* pB = reinterpret_cast<ProvisionBox*>(bodyB->GetUserData().pointer);
    pB->apply_effect(wA);
}

void MyListener::execute_contact_jump(b2Body* bodyA, b2Body* bodyB) {
    // This functions check if the worm is jumping or falling and applies damage if it falls too
    // much It also smoothes the landing of the worm if it was jumping or backflipping
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    wA->add_contact();
    if (wA->get_state() == JUMPING || wA->get_state() == FALLING ||
        wA->get_state() == BACKFLIPPING) {
        if (wA->get_state() == JUMPING || wA->get_state() == BACKFLIPPING) {
            wA->set_state(STILL);
            bodyA->SetLinearVelocity(b2Vec2(0, 0));
        }
        float y_diff = bodyA->GetPosition().y - wA->get_last_y();
        if (y_diff < -FALL_DISTANCE_THRESHOLD) {
            int damage = abs(std::round(y_diff));
            if (damage > FALL_DAMAGE_THRESHOLD) {
                wA->apply_damage(FALL_DAMAGE_THRESHOLD);
            } else {
                wA->apply_damage(damage);
            }
        }
    }
}

void MyListener::BeginContact(b2Contact* contact) {

    if (contact->IsTouching() == false) {
        return;
    }

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    handle_begin_contact(bodyA, bodyB);
    handle_begin_contact(bodyB, bodyA);
}

void MyListener::change_last_y(b2Body* bodyA, b2Body* bodyB) {
    // This function changes the last_y of the worm to the current y so it can then calculate fall
    // damage
    Worm* wA = reinterpret_cast<Worm*>(bodyA->GetUserData().pointer);
    wA->remove_contact();
    wA->set_last_y(bodyA->GetPosition().y);
}

void MyListener::EndContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    handle_end_contact(bodyA, bodyB);
    handle_end_contact(bodyB, bodyA);
}

MyListener::~MyListener() {}
