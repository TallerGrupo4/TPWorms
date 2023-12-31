#include "projectile.h"

Projectile::Projectile(const ProjectileSnapshot& proj_snpsht,
                       std::shared_ptr<EffectsAnimations>& effects_an,
                       std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces,
                       SDL2pp::Renderer& renderer):
        proj_an(renderer, surfaces),
        effects_an(effects_an),
        effects_sound(effects_sound),
        facing_left(proj_snpsht.direction == LEFT ? true : false),
        angle(proj_snpsht.angle),
        id(proj_snpsht.id),
        state(static_cast<ProjectileStates>(proj_snpsht.state)),
        type(static_cast<ProjectileTypes>(proj_snpsht.type)),
        x(proj_snpsht.pos_x),
        y((-1) * proj_snpsht.pos_y),
        explosion_size(proj_snpsht.explosion_radius * RESOLUTION_MULTIPLIER),
        width(std::round(proj_snpsht.width * 5)),
        height(std::round(proj_snpsht.height * 5)),
        exhaust_timer(0) {
    switch (type) {
        case ProjectileTypes::DynamiteProj:
            effects_sound->play_dynamite_active_sound();
            break;
        case ProjectileTypes::BazookaProj:
            effects_sound->play_bazooka_shoot_sound();
            break;
        case ProjectileTypes::HolyGrenadeProj:
            effects_sound->play_holy_grenade_active_sound();
            break;
        default:
            break;
    }
}

void Projectile::update_from_snapshot(SDL2pp::Renderer& renderer, ProjectileSnapshot& proj_snpsht) {
    angle = proj_snpsht.angle;
    facing_left = proj_snpsht.direction == LEFT ? true : false;
    state = static_cast<ProjectileStates>(proj_snpsht.state);
    x = proj_snpsht.pos_x;
    y = (-1) * proj_snpsht.pos_y;
    proj_an.update_from_snapshot(state, type);
    switch (state) {
        case ProjectileStates::EXPLODED:
            switch (type) {
                case ProjectileTypes::FragmentProj:
                    effects_an->set_small_explosion_an(renderer, x, y, explosion_size);
                    effects_sound->play_small_explosion_sound();
                    break;
                case ProjectileTypes::HolyGrenadeProj:
                    effects_an->set_big_explosion_an(renderer, x, y, explosion_size);
                    effects_sound->play_holy_grenade_explosion_sound();
                    break;

                case ProjectileTypes::DynamiteProj:
                    effects_sound->stop_dynamite_fuse_sound();

                default:
                    effects_an->set_big_explosion_an(renderer, x, y, explosion_size);
                    effects_sound->play_big_explosion_sound();
                    break;
            }
            break;

        case ProjectileStates::ALIVE:
            if ((type == ProjectileTypes::BazookaProj) or (type == ProjectileTypes::MortarProj) or
                (type == ProjectileTypes::AirStrikeProj)) {
                if (exhaust_timer == 1) {
                    effects_an->set_missile_exhaust_an(renderer, x, y);
                    exhaust_timer = 0;
                } else {
                    exhaust_timer++;
                }
            }
            break;
    }
}

void Projectile::update_from_iter(int iter) {
    for (int i = 0; i < iter; i++) {
        proj_an.update_from_iter(state, type, angle);
    }
}

void Projectile::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    int top_left_x = (x - width / 2) * RESOLUTION_MULTIPLIER +
                     (int)(renderer.GetLogicalWidth() / 2) - camera_offset_x;
    int top_left_y = (y - height / 2) * RESOLUTION_MULTIPLIER +
                     (int)(renderer.GetLogicalHeight() / 2) - camera_offset_y;

    proj_an.render(state, type, angle, renderer,
                   SDL2pp::Rect(top_left_x, top_left_y, width * RESOLUTION_MULTIPLIER,
                                height * RESOLUTION_MULTIPLIER),
                   facing_left);
}

ProjectileStates Projectile::get_proj_state() { return this->state; }
int Projectile::get_proj_x() { return this->x; }
int Projectile::get_proj_y() { return this->y; }
