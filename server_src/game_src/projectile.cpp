#include "projectile.h"
#include "game_constants.h"

#define EXPLOSION_POWER ConfigSingleton::getInstance().get_explosion_power()
#define EXPLOSION_FRAGMENT_POWER ConfigSingleton::getInstance().get_explosion_fragment_power()
#define FRAGMENT_DAMAGE ConfigSingleton::getInstance().get_fragment_damage()


Projectile::Projectile(b2Body* body, int damage, int radius, ProjectileTypes type, ExplosionType explosion_type, int timer, int fragments, float angle, bool affected_by_wind):
 Entity(body, PROJECITLE), damage(damage), radius(radius), projectile_type(type), explosion_type(explosion_type), radius_body_size(0.2), timer(timer), fragments(fragments), angle(angle), state(ALIVE) , id(INVALID), affected_by_wind(affected_by_wind)  {
        body->GetUserData().pointer = (uintptr_t) this;
        body->SetTransform(body->GetPosition(), angle);
    }

Projectile::~Projectile() {}

bool Projectile::is_affected_by_wind(){
    return affected_by_wind;
}

void Projectile::decresease_timer(int tick) {
    if (timer > 0){
        timer -= tick;
    }
}

int Projectile::get_timer() {
    return timer;
}

void Projectile::explode(std::unordered_set<std::shared_ptr<Projectile>>& projectiles) {
    set_state(EXPLODED);
    if (projectile_type == FragmentProj){
        Explosion ex(explosion_type, fragments, FRAGMENT_DAMAGE, radius, damage, EXPLOSION_FRAGMENT_POWER);
        ex.explode(body, projectiles);

    } else {
        Explosion ex(explosion_type, fragments, FRAGMENT_DAMAGE, radius, damage, EXPLOSION_POWER);
        ex.explode(body, projectiles);
    }
}


ExplosionType Projectile::get_explosion_type() {
    return explosion_type;
}

void Projectile::set_state(char state) {
    this->state = state;
}

int Projectile::get_state() {
    return state;
}

ProjectileTypes Projectile::get_projectile_type() {
    return projectile_type;
}

int Projectile::get_fragments() {
    return fragments;
}

int Projectile::get_fragment_damage() {
    return FRAGMENT_DAMAGE;
}

float Projectile::get_angle(){
    float angle = body->GetAngle() ;
    float normalized_angle = fmod(angle, PI);
    int degree = round(normalized_angle * RADTODEG);
    return degree;
}

int Projectile::get_direction(){
    float speed_x = body->GetLinearVelocity().x;
    if (speed_x >= 0){
        return DER;
    }
    return IZQ;
}

void Projectile::set_angle(float angle) {
    body->SetTransform(body->GetPosition(), angle);
}

void Projectile::set_id(char id) {
    this->id = id;
}

char Projectile::get_id() {
    return id;
}

ProjectileSnapshot Projectile::get_snapshot() {
    float pos_x = body->GetPosition().x;
    float pos_y = body->GetPosition().y;
    return ProjectileSnapshot(projectile_type, pos_x, pos_y, get_angle(), get_direction(), radius_body_size, state, id, radius);
}


