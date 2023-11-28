#include "tool_bat.h"
#include "tool_bat_callback.h"
#include "worm.h"
#include "game_constants.h"

#define BAT_DAMAGE ConfigSingleton::getInstance().get_baseball_bat_damage()


Bat::Bat() : Tool(BAT, 0, 0, false), damage(BAT_DAMAGE) {}

void Bat::use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
        float lower_angle = angle - 45 * DEGTORAD;
        for (int i = 0 ; i < 10 ; i++){
            float current_angle = lower_angle + (i/(float)10) * 90 * DEGTORAD;
            b2RayCastBat callback;
            b2Vec2 pos = worm->GetPosition();
            float dir_x = direction * cos(current_angle);
            float dir_y = sin(current_angle);
            b2Vec2 direction = b2Vec2(dir_x , dir_y);
            b2Vec2 endPos = pos + 2 * direction;
            worm->GetWorld()->RayCast(&callback, pos, endPos);
            if (callback.body){
                if (callback.body->GetType() == b2_dynamicBody){
                    Worm* wB = reinterpret_cast<Worm*>(callback.body->GetUserData().pointer);
                    if (wB && wB->get_type() == WORM){
                        wB->apply_damage(BAT_DAMAGE);
                        callback.body->ApplyLinearImpulseToCenter( b2Vec2(  direction.x,  direction.y), true);
                    }
                }
            }
        }
}

Bat::~Bat(){}