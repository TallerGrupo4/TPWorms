#include "projectile.h"

Projectile::Projectile(b2Body* body, int damage, int radius, int type, int explosion_type, int timer, int fragments, int fragment_damage, float angle) :
    body(body), damage(damage), radius(radius), type(type), body_type(PROJECITLE), explosion_type(explosion_type), timer(timer), fragments(fragments), fragment_damage(fragment_damage), angle(angle)/*, state(state)*/  {
        body->GetUserData().pointer = (uintptr_t) this;
    }

Projectile::~Projectile() {}

b2Body* Projectile::get_body(){
    return body;
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
    Explosion ex(explosion_type, fragments, fragment_damage, radius, damage);
    ex.explode(body, projectiles);
}

int Projectile::get_type() {
    return type;
}

int Projectile::get_explosion_type() {
    return explosion_type;
}

void Projectile::set_state(char state) {
    this->state = state;
}

int Projectile::get_state() {
    return state;
}

int Projectile::get_fragments() {
    return fragments;
}

int Projectile::get_fragment_damage() {
    return fragment_damage;
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

ProjectileSnapshot Projectile::get_snapshot() {
    float pos_x = body->GetPosition().x;
    float pos_y = body->GetPosition().y;
    return ProjectileSnapshot(type, pos_x, pos_y, get_angle());
}


