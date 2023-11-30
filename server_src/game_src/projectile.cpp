#include "projectile.h"
#include "game_constants.h"


Projectile::Projectile(b2Body* body, int damage, int radius, ProjectileTypes type, ExplosionType explosion_type, int timer, int fragments, float angle):
 Entity(body, PROJECITLE), damage(damage), radius(radius), type(type), explosion_type(explosion_type), radius_body_size(0.2), timer(timer), fragments(fragments), angle(angle), state(ALIVE) , id(INVALID)  {
        body->GetUserData().pointer = (uintptr_t) this;
        body->SetTransform(body->GetPosition(), angle);
    }

Projectile::~Projectile() {}



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
    printf("Projectile::explode\n");
    ex.explode(body, projectiles);
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

void Projectile::set_id(char id) {
    this->id = id;
}

char Projectile::get_id() {
    return id;
}

ProjectileSnapshot Projectile::get_snapshot() {
    float pos_x = body->GetPosition().x;
    float pos_y = body->GetPosition().y;
    return ProjectileSnapshot(type, pos_x, pos_y, get_angle(), get_direction(), radius_body_size, state, id, explosion_type);
}


