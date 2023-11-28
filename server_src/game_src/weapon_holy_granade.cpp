#include "weapon_holy_granade.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define HOLY_GRANADE_DAMAGE ConfigSingleton::getInstance().get_holy_granade_damage()
#define HOLY_GRANADE_RADIUS ConfigSingleton::getInstance().get_holy_granade_radius()
#define HOLY_GRANADE_RESTITUTION ConfigSingleton::getInstance().get_holy_granade_restitution()
#define HOLY_GRANADE_DENSITY ConfigSingleton::getInstance().get_holy_granade_density()

HolyGranade::HolyGranade() : Weapon(HOLY_GRANADE, -1 , -1 , HOLY_GRANADE_DAMAGE, HOLY_GRANADE_RADIUS, 0 , 0 , 0, true, true, true) {}

void HolyGranade::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* HolyGranade::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y,HOLY_GRANADE_RESTITUTION, HOLY_GRANADE_DENSITY );
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}


HolyGranade::~HolyGranade() {}
