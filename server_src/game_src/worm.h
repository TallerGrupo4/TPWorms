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
    char id;
    int life;
    int state;
    int curr_weapon;
    int act_dir;
    float last_still_angle;
    float last_y;
    int number_contacts;
    int type;
    // std::unordered_map<int, int> weapons;
    
    WormData(char id): id(id), life(START_LIFE), state(STILL), curr_weapon(NO_WEAPON) , act_dir(DER) , last_still_angle(0), last_y(0), number_contacts(0) , type(WORM)  {
        //TODO insert weapons with their respective starting ammo
    }

    public:


    int get_type(){
        return type;
    }

    int get_state(){
        return state;
    }

    void set_state(int new_state){
        state = new_state;
    }

    void set_last_still_angle(float angle){
        last_still_angle = angle;
    }

    float last_angle(){
        return last_still_angle;
    }

    float get_last_y(){
        return last_y;
    }

    void set_last_y(float y){
        last_y = y;
    }

    void apply_damage(int damage){
        life -= damage;
        state = DAMAGED;
        if (life <= 0){
            life = 0;
            state = DEAD;
        }
    }


    void add_contact(){
        number_contacts++;
    }

    void remove_contact(){
        number_contacts--;
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

    int get_angle(){
        if (body == nullptr){throw WormNotFound();}
        float angle = body->GetAngle() ;
        float normalized_angle = fmod(angle, PI);
        int degree = round(normalized_angle * RADTODEG);
        return degree;
    }

    void move(int dir){
        if (!in_contact()) {return;}
        if (data.state != STILL && data.state != MOVING && data.state != CLIMBING) {return;}
        data.act_dir = dir;
        body->SetLinearVelocity( b2Vec2( 0, 0 ) );
        float m = body->GetMass();
        float impulse_x = dir * WORM_SPEED * cos(body->GetAngle()) * m;
        float impulse_y = dir * WORM_SPEED * sin(body->GetAngle()) * m;
        body->ApplyLinearImpulseToCenter( b2Vec2(impulse_x , impulse_y) , true);
        if (get_angle() != 0){
            data.state = CLIMBING;
        } else{
            data.state = MOVING;
        }
    }

    void jump (int dir){
        if (data.state != STILL && !in_contact()) {return;}
        data.state = JUMPING;
        body->SetLinearVelocity( b2Vec2( 0, 0 ) );
        float m = body->GetMass();
        if (dir == FOWARD) {
            body->ApplyLinearImpulseToCenter( b2Vec2( m * WORM_JUMP_HOR_SPEED * data.act_dir, m * WORM_JUMP_SPEED), true );
        }
        else if (dir == BACKWARD) {
            body->ApplyLinearImpulseToCenter( b2Vec2( m * -WORM_BACKFLIP_HOR_SPEED * data.act_dir,m * WORM_BACKFLIP_SPEED), true );
        }
    }

    bool in_contact(){
        return data.number_contacts > 0;
    }

    void add_contact(){
        data.number_contacts++;
    }

    void remove_contact(){
        data.number_contacts--;
    }
    


    // void jump(int direction){
    //     if (data.state != STILL) {return;}
    //     if (direction == FOWARD){
    //         body->SetLinearVelocity( b2Vec2( 0, 0 ) );
    //         float vel_x = data.act_dir * WORM_JUMP_HOR_SPEED ;
    //         float vel_y = WORM_JUMP_SPEED;
    //         body->SetLinearVelocity( b2Vec2( vel_x, vel_y ) );
    //         data.state = JUMPING;

    //     } else {
    //         float vel_x = -1 * data.act_dir * WORM_BACKFLIP_SPEED ;
    //         float vel_y = WORM_BACKFLIP_HEIGHT;
    //         body->SetLinearVelocity( b2Vec2( vel_x, vel_y ) );
    //         data.state = BACKFLIPPING;
    //     }
    // }

    WormSnapshot get_snapshot() {
        float pos_x ; float pos_y ; int angle;
        if (body == nullptr){ // SHOULD DECIDE WHAT TO DO WITH WORM BODY OR SOMETHING
            pos_x = 0;
            pos_y = 0;
            angle = 0;
        } else {
            pos_x = body->GetPosition().x;
            pos_y = body->GetPosition().y;
            angle = get_angle();
        }
        WormSnapshot snapshot(data.id, pos_x, pos_y, angle, START_LIFE, data.life, data.act_dir, data.curr_weapon, data.state);
        return snapshot;
    }

    int get_state(){
        return data.state;
    }

    void set_state(int new_state){
        data.state = new_state;
    }

    void set_last_still_angle(float angle){
        data.last_still_angle = angle;
    }

    float last_angle(){
        return data.last_still_angle;
    }




};

#endif  // WORM_H