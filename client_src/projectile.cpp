#include "projectile.h"

Projectile::Projectile(ProjectileSnapshot proj_snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) :
    proj_an(renderer, surfaces),
    facing_left(proj_snpsht.direction == LEFT ? true : false),
    angle(proj_snpsht.angle),
    id(proj_snpsht.id),
    state(static_cast<ProjectileStates>(proj_snpsht.state)),
    type(static_cast<ProjectileTypes>(proj_snpsht.type)),
    x(proj_snpsht.pos_x),
    y((-1)*proj_snpsht.pos_y),
    explosion_type(proj_snpsht.explosion_type),
    width(proj_snpsht.width),
    height(proj_snpsht.height) {

}

void Projectile::update_from_snapshot(ProjectileSnapshot& proj_snpsht) {
    angle = proj_snpsht.angle;
    facing_left = proj_snpsht.direction == LEFT ? true : false;
    state = static_cast<ProjectileStates>(proj_snpsht.state);
    x = proj_snpsht.pos_x;
    y = (-1)*proj_snpsht.pos_y;
    proj_an.update_from_snapshot(state, type);
}

void Projectile::update_from_iter(int iter) {
    for (int i = 0; i < iter; i++) {
        proj_an.update_from_iter(state, type, angle);
    }
}

void Projectile::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    int top_left_x = (x-width/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_left_y = (y-height/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;
    //std::cout << "top_left_x: " << top_left_x << " top_left_y: " << top_left_y << std::endl;
    
    proj_an.render(state, type, angle, renderer, SDL2pp::Rect(top_left_x, top_left_y, width*RESOLUTION_MULTIPLIER,
                        height*RESOLUTION_MULTIPLIER),
                        facing_left);
    // if(state != DEAD) {
    //     worm_texts.render(renderer, top_left_x + width*RESOLUTION_MULTIPLIER/2, top_left_y, top_left_y + height*RESOLUTION_MULTIPLIER);
    // }
}

ProjectileStates Projectile::get_proj_state() {
    return this->state;
}
int Projectile::get_proj_x() {
    return this->x;
}
int Projectile::get_proj_y() {
    return this->y;
}
bool Projectile::proj_facing_left() {
    return this->facing_left;
}