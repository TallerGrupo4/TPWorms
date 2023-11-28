#include "weapon_airstrike.h"
#include "weapon_airstrike_callback.h"


Airstrike::Airstrike(): Weapon(AIRSTRIKE_TYPE, AIRSTRIKE_MAX_AMMO, AIRSTRIKE_MAX_AMMO, AIRSTRIKE_DAMAGE, AIRSTRIKE_RADIUS, 0 , 0 , 0, true, false, false) {}


float Airstrike::get_roof_height(b2Body* body){
        b2Vec2 direction = b2Vec2(0 , 1);
        
        b2RayCastStrike callback;
        b2Vec2 endPos = b2Vec2(0, 200);

        body->GetWorld()->RayCast(&callback, b2Vec2(0, 0), endPos);
        float max_y = 0;

        for (auto it = callback.bodies.begin(); it != callback.bodies.end(); it++){
            b2Body* body = *it;
            if (body->GetPosition().y > max_y){
                max_y = body->GetPosition().y;
            }
        }
        return max_y;
}

Projectile* Airstrike::shoot_airstrike_projectile(b2Body* worm, float x, float y){
    b2Vec2 pos = b2Vec2(x, y);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.bullet = true;
    b2Body* body = worm->GetWorld()->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 0.2;

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 0.5;
    body->CreateFixture(&fixture);

    body->ApplyLinearImpulseToCenter(b2Vec2(0, -1), true);

    return new Projectile(body, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, -90 * DEGTORAD);
}


void Airstrike::use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
        float roof_height = get_roof_height(worm);

        std::vector<float> possible_xs = {-1.5 , -1 , -0.5 , 0 , 0.5 , 1 , 1.5};
        std::vector<float> possible_ys = {-3 , -4 , -2 , -1 , -5};
        
        for (int i = 0 ; i < 6 ; i++){
            int random = rand() % possible_xs.size();
            float pos_x = possible_xs[random];
            possible_xs.erase(possible_xs.begin() + random);
            random = rand() % possible_ys.size();
            float pos_y = possible_ys[random];
            Projectile* p = shoot_airstrike_projectile(worm, pos_x + x, roof_height + y);
            projectiles.insert(std::shared_ptr<Projectile>(p));
        }
}

Airstrike::~Airstrike() {}
