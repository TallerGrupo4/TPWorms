#include "weapon_red_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define RED_GRANADE_DAMAGE ConfigSingleton::getInstance().get_red_granade_damage()
#define RED_GRANADE_RADIUS ConfigSingleton::getInstance().get_red_granade_radius()
#define RED_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_red_granade_restitution()
#define RED_GRANADE_DENSITY ConfigSingleton::getInstance().get_red_granade_density()

RedGranade::RedGranade() : Weapon(RED_GRANADE, -1 , -1 , RED_GRANADE_DAMAGE, RED_GRANADE_RADIUS, 0 , 0 , 0, true, true, true) {}

void RedGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* RedGranade::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y,RED_GRANADE_RESTITUTION, RED_GRANADE_DENSITY );
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

RedGranade::~RedGranade(){}
