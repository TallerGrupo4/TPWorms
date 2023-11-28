#include "weapon_mortar.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define MORTAR_DAMAGE ConfigSingleton::getInstance().get_mortar_damage()
#define MORTAR_RADIUS ConfigSingleton::getInstance().get_mortar_radius()
#define MORTAR_RESTITUTION ConfigSingleton::getInstance().get_mortar_misile_restitution()
#define MORTAR_DENSITY ConfigSingleton::getInstance().get_mortar_misile_density()

Mortar::Mortar() : Weapon(MORTAR, -1 , -1 , MORTAR_DAMAGE, MORTAR_RADIUS, 0 , 0 , 0, true, true, true) {}

void Mortar::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* Mortar::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y,MORTAR_RESTITUTION, MORTAR_DENSITY );
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

Mortar::~Mortar(){}

