#include "worm.h"
#include "worm_comprobator.h"

WormComprobator::WormComprobator(){}


void WormComprobator::check_during_game(std::list<std::shared_ptr<Worm>>& worms, int& time, int& current_id, int& height , int& width, int& water_level){
    for (auto& w : worms){
        if (w->state == DEAD){
            continue;
        }
        if (check_out_of_map_worm(*w, time, current_id, height , width, water_level)){
            continue;
        }
        
        check_states(*w, time, current_id);
        check_angles(*w);
        check_velocities(*w);
    }
}



std::list<char> WormComprobator::check_post_game(std::list<std::shared_ptr<Worm>>& worms, b2World& world){
    std::list<char> dead_worms;
    for (auto& w : worms){
        if (w->state == DAMAGED || w->state == SHOOTED){
            w->state = STILL;
        }

        if (w->state == DEAD && w->body != nullptr) {
            world.DestroyBody(w->body);
            w->body = nullptr;
            dead_worms.push_back(w->id);
        }
    }
    return dead_worms;
}

bool WormComprobator::have_worm_finished_turn(std::list<std::shared_ptr<Worm>>& worms, int& cleaning_time){
    for (auto& w: worms){
        if (w->get_state() == DEAD) {continue;}
        w->set_used_tool(false);
        w->reset_aiming_angle();
        if (w->state == AIMING) {
            w->set_state(STILL);
        }
        w->store_tool();
        if (w->get_state() != DEAD && w->body->GetLinearVelocity() != b2Vec2_zero || w->body->GetAngularVelocity() != 0){
            cleaning_time = 1 * FPS;
            return false;
        }
    }
    return true;
}

void WormComprobator::check_angles(Worm& w){
    // To avoid the worm from spinning when angle is too big
    if (abs (w.get_angle()) >= ANG_THRESHOLD){
        b2Body* body = w.body;
        body->SetTransform(body->GetPosition(), w.last_angle());
    }
}

void WormComprobator::check_states(Worm& w, int& turn_time, int& current_turn_player_id){
    // To skip turn if damaged
    if (w.get_state() == DAMAGED){
        if (current_turn_player_id == w.get_id()) {
            turn_time = 0;
            return;
        }
    }
    // To let the worm shoot in peace
    if (w.get_state() == SHOOTED || w.get_state() == AIMING) {return;}

    // To apply slide when angle is too big and correct angle
    if (w.get_number_contacts() == 1){
        b2Body* body = w.body->GetContactList()->other;
        if (body && body->GetType() == b2_staticBody){
            if (body->GetFixtureList()->GetFriction() == 0){
                w.set_state(SLIDING);
            }
            w.body->SetTransform(w.body->GetPosition(), body->GetAngle());
            w.set_last_still_angle(body->GetAngle());
        }
    }
    // To apply the falling state
    float diff = w.body->GetPosition().y - w.get_last_y();
    if (diff < -1.5 && w.get_state() != FALLING && !w.in_contact() && w.body->GetLinearVelocity().Length() > 1){
        w.set_state(FALLING);
    }
    // To apply the still state
    if (w.body->GetLinearVelocity() == b2Vec2_zero && w.body->GetAngularVelocity() == 0){
        w.set_state(STILL);
    }
}

void WormComprobator::check_velocities(Worm& w){
    // So the worm doens't freeze the gaming until it's still completely
    if (w.body->GetLinearVelocity().Length() < VEL_THRESHOLD ){
        w.body->SetLinearVelocity(b2Vec2_zero);
        w.body->SetAngularVelocity(0);
    } 
    // To avoid the worm from moving a lot when down in a slope
    if (w.state == CLIMBING){
        if (w.act_dir == LEFT && w.get_angle() > 0){
            w.body->ApplyForceToCenter(b2Vec2(5 * w.body->GetMass(),0), true);
        }
        if (w.act_dir == RIGHT && w.get_angle() < 0){
            w.body->ApplyForceToCenter(b2Vec2(-5 * w.body->GetMass(),0), true);
        }
    }
    // To avoid the worm from spinning when 
    if (abs (w.body->GetAngularVelocity()) > 0){
        w.body->SetAngularVelocity(0);
    }

}

bool WormComprobator::check_out_of_map_worm(Worm& w, int& turn_time, int& current_turn_player_id, int& height , int& width, int& water_level){
    // To avoid the worm from going out of the map
   float w_x = w.body->GetPosition().x;
   float w_y = w.body->GetPosition().y;
   if (w_x < -width/2 || w_x > width/2 || w_y < -height/2 || w_y > height/2|| w_y < water_level){
       w.set_state(DEAD);
       w.body->SetLinearVelocity(b2Vec2_zero);
       w.body->SetAngularVelocity(0);
       w.body->SetGravityScale(0);
       if (current_turn_player_id == w.get_id()){
           turn_time = 0;
       }
       return true;
   } else {
         return false;
   }
}

WormComprobator::~WormComprobator(){}