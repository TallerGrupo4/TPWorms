#include "projectile.h"

Projectile::Projectile(ProjectileSnapshot proj_snpsht, std::shared_ptr<EffectsAnimations>& effects_an, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) :
    proj_an(renderer, surfaces),
    effects_an(effects_an),
    facing_left(proj_snpsht.direction == LEFT ? true : false),
    angle(proj_snpsht.angle),
    id(proj_snpsht.id),
    state(static_cast<ProjectileStates>(proj_snpsht.state)),
    type(static_cast<ProjectileTypes>(proj_snpsht.type)),
    x(proj_snpsht.pos_x),
    y((-1)*proj_snpsht.pos_y),
    explosion_type(proj_snpsht.explosion_type),
    width(std::round(proj_snpsht.width*5)),
    height(std::round(proj_snpsht.height*5)),
    exhaust_timer(0) {
        std::cout << "projectile " << +id << " type: " << +type << std::endl;
        std::cout << "state: " << +state << std::endl;
        std::cout << "explosion_type: " << explosion_type << std::endl;
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;
        std::cout << "angle: " << angle << std::endl;
        std::cout << "facing_left: " << facing_left << std::endl;
}

void Projectile::update_from_snapshot(SDL2pp::Renderer& renderer, ProjectileSnapshot& proj_snpsht) {
    angle = proj_snpsht.angle;
    facing_left = proj_snpsht.direction == LEFT ? true : false;
    state = static_cast<ProjectileStates>(proj_snpsht.state);
    x = proj_snpsht.pos_x;
    y = (-1)*proj_snpsht.pos_y;
    proj_an.update_from_snapshot(state, type);
    if(state == EXPLODED) {
        if(type == FragmentProj) {
            effects_an->set_small_explosion_an(renderer, x, y);
        } else {
            effects_an->set_big_explosion_an(renderer, x, y);
        }
    } else if (state == ALIVE) {
        if((type == BazookaProj) or (type == MortarProj) or (type == AirStrikeProj)) {
            if(exhaust_timer == 1) {
                effects_an->set_missile_exhaust_an(renderer, x, y);
                exhaust_timer = 0;
            } else {
                exhaust_timer++;
            }
        }
    }
}

void Projectile::update_from_iter(int iter) {
    std::cout << "update_from_iter\n";
    std::cout << "id: " << +id << std::endl;
    std::cout << "type: " << +type << std::endl;
    std::cout << "state: " << +state << std::endl;
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
