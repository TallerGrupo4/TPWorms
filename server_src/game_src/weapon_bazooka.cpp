#include "weapon_bazooka.h"
#include "../config.h"
#include "../../common_src/constants.h"

#define BAZOOKA_DAMAGE ConfigSingleton::getInstance().get_bazooka_damage()
#define BAZOOKA_RADIUS ConfigSingleton::getInstance().get_bazooka_radius()

Bazooka::Bazooka() : Weapon(BAZOOKA, 1 , BAZOOKA_DAMAGE, BAZOOKA_RADIUS, 0 , 0 , 0, true, true, true) {}

void Bazooka::use(b2Body* worm, int direction, float angle , int time,  int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles){
    std::shared_ptr<Projectile> projectile(create_projectile(worm, direction, angle, power));
    projectiles.insert(projectile);

    projectile->get_body()->ApplyLinearImpulseToCenter(b2Vec2(direction *cos(angle) * power, sin(angle) * power), true);
}



Projectile* Bazooka::create_projectile(b2Body* worm, int direction, float angle , int power){
    float pos_x = worm->GetPosition().x + direction * cos(angle) * OFFSET;
    float pos_y = worm->GetPosition().y + sin(angle) * OFFSET;

    b2Body* projectileBody = create_projectile_body(worm->GetWorld(), angle, pos_x, pos_y);
    // explosion_type = EXPLOSIVE
    Projectile* projectile = new Projectile(projectileBody, damage, radius, type, EXPLOSIVE, 0, fragments, fragment_damage, angle);

    return projectile;
}

