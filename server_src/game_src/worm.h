#include <vector>
#include <unordered_map>

#include <box2d/box2d.h>

#include "../../common_src/constants.h"
#include "../../common_src/snapshot.h"
#include "game_constants.h"
// #include "weapons.h"

#ifndef WORM_H
#define WORM_H

class WormNotFound: public std::exception {
    const char* what() const noexcept override {
        return "The worm body is a null pointer";
    }
};


class WormData{
    friend class Worm;
    // friend class ProjectileListener;
    // friend class JumpListener;
    char id;
    int life;
    int state;
    int curr_weapon = NO_WEAPON;
    int act_dir = DER;
    int type;
    // std::unordered_map<int, int> weapons;
    
    WormData(char id): id(id), life(START_LIFE), state(STILL), type(WORM) {
        //TODO insert weapons with their respective starting ammo
    }

    public:

    int get_state(){
        return state;
    }

    void set_state(int new_state){
        state = new_state;
    }

    ~WormData(){}

};

class Worm {
    friend class Game;
    b2Body* body;
    WormData data;


public:
    Worm(b2Body* body, char id):
        body(body), data(id) {
            body->GetUserData().pointer = (uintptr_t) &data;
        }

    void move(int direction) {
        if (data.state == MOVING || data.state == STILL){
            data.act_dir = direction;
            body->SetLinearVelocity( b2Vec2( 0, 0 ) );
            float vel_x = direction * WORM_SPEED;
            body->SetLinearVelocity( b2Vec2( vel_x, 0 ) );
            data.state = MOVING;
        }
    }

    void jump(int direction){
        if (data.state != STILL) {return;}
        if (direction == FOWARD){
            body->SetLinearVelocity( b2Vec2( 0, 0 ) );
            float vel_x = data.act_dir * WORM_JUMP_SPEED ;
            float vel_y = WORM_JUMP_HEIGHT;
            body->SetLinearVelocity( b2Vec2( vel_x, vel_y ) );
            data.state = JUMPING;

        } else {
            float vel_x = -1 * data.act_dir * WORM_BACKFLIP_SPEED ;
            float vel_y = WORM_BACKFLIP_HEIGHT;
            body->SetLinearVelocity( b2Vec2( vel_x, vel_y ) );
            data.state = BACKFLIPPING;
        }
    }

    WormSnapshot get_snapshot() {
        if (body == nullptr){throw WormNotFound();}
        float pos_x = body->GetPosition().x;
        float pos_y = body->GetPosition().y;
        float angle = body->GetAngle();
        WormSnapshot snapshot(data.id, pos_x, pos_y, angle, START_LIFE, data.life, data.act_dir, data.curr_weapon, data.state);
        return snapshot;
    }

    int get_state(){
        return data.state;
    }

    void set_state(int new_state){
        data.state = new_state;
    }


};

#endif  // WORM_H