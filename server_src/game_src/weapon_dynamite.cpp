#include "weapon_dynamite.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define DYNAMITE_DAMAGE ConfigSingleton::getInstance().get_dynamite_damage()
#define DYNAMITE_RADIUS ConfigSingleton::getInstance().get_dynamite_radius()
#define DYNAMITE_RESTITUTION ConfigSingleton::getInstance().get_dynamite_restitution()
#define DYNAMITE_DENSITY ConfigSingleton::getInstance().get_dynamite_density()

Dynamite::Dynamite() : Weapon(DYNAMITE, -1 , -1 , DYNAMITE_DAMAGE, DYNAMITE_RADIUS, 0 , 0 , 0, true, true, true) {}

void Dynamite::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* Dynamite::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y, DYNAMITE_RESTITUTION, DYNAMITE_DENSITY);
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

Dynamite::~Dynamite(){}

