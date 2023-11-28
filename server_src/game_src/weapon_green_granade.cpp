#include "weapon_green_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define GREEN_GRANADE_DAMAGE ConfigSingleton::getInstance().get_green_granade_damage()
#define GREEN_GRANADE_RADIUS ConfigSingleton::getInstance().get_green_granade_radius()
#define GREEN_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_green_granade_restitution()
#define GREEN_GRANADE_DENSITY ConfigSingleton::getInstance().get_green_granade_density()

GreenGranade::GreenGranade() : Weapon(GREEN_GRANADE, -1 , -1 , GREEN_GRANADE_DAMAGE, GREEN_GRANADE_RADIUS, 0 , 0 , 0, true, true, true) {}

void GreenGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* GreenGranade::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y,GREEN_GRANADE_RESTITUTION, GREEN_GRANADE_DENSITY );
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

GreenGranade::~GreenGranade(){}

