#include "weapon_banana.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define BANANA_DAMAGE ConfigSingleton::getInstance().get_banana_damage()
#define BANANA_RADIUS ConfigSingleton::getInstance().get_banana_radius()
#define BANANA_RESTITUTION ConfigSingleton::getInstance().get_banana_restitution()
#define BANANA_DENSITY ConfigSingleton::getInstance().get_banana_density()

Banana::Banana() : Weapon(BANANA, -1 , -1 , BANANA_DAMAGE, BANANA_RADIUS, 0 , 0 , 0, true, true, true) {}

void Banana::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* Banana::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;


    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y, BANANA_RESTITUTION, BANANA_DENSITY);
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

Banana::~Banana(){}
