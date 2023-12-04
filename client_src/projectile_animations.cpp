#include "projectile_animations.h"

ProjectileAnimations::ProjectileAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces) :
                                ban_an(renderer, surfaces.banana, SECS_FOR_GRENADES_SPRITES),
                                gr_an(renderer, surfaces.grenade, SECS_FOR_GRENADES_SPRITES),
                                cls_an(renderer, surfaces.cluster_bomb, SECS_FOR_GRENADES_SPRITES),
                                cls_fragment_an(renderer, surfaces.cluster_bomb_fragments, SECS_FOR_FRAGMENTS_SPRITES),
                                dyn_an(renderer, surfaces.dynamite, SECS_FOR_DYNAMITE_SPRITES),
                                holy_grenade_an(renderer, surfaces.holy_grenade, SECS_FOR_GRENADES_SPRITES),
                                bazooka_missile_an(renderer, surfaces.bazooka_missile, 0),
                                mortar_round_an(renderer, surfaces.mortar_round, 0),
                                air_missile_an(renderer, surfaces.air_missile, 0) {

}

void ProjectileAnimations::render(ProjectileStates state, ProjectileTypes type, int angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       const bool facing_left,
                       int left_offset,
                       int right_offset,
                       int above_offset,
                       int bellow_offset) {

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    switch (state) {
    case ProjectileStates::ALIVE:
        switch (type) {
        case ProjectileTypes::BananaProj:
            ban_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::GreenGrenadeProj:
            gr_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::RedGrenadeProj:
            cls_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::FragmentProj:
            cls_fragment_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::DynamiteProj:
            dyn_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::HolyGrenadeProj:
            holy_grenade_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::BazookaProj:
            bazooka_missile_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::MortarProj:
            mortar_round_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        case ProjectileTypes::AirStrikeProj:
            air_missile_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void ProjectileAnimations::update_from_snapshot(ProjectileStates state, ProjectileTypes type) {
    switch (state) {
    case ProjectileStates::ALIVE:
        switch (type) {
        case ProjectileTypes::BananaProj:
            ban_an.update_once();
            break;
        case ProjectileTypes::GreenGrenadeProj:
            gr_an.update_once();
            break;
        case ProjectileTypes::RedGrenadeProj:
            cls_an.update_once();
            break;
        case ProjectileTypes::FragmentProj:
            cls_fragment_an.update_once();
            break;
        case ProjectileTypes::DynamiteProj:
            dyn_an.update_once();
            break;
        case ProjectileTypes::HolyGrenadeProj:
            holy_grenade_an.update_once();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void ProjectileAnimations::update_from_iter(ProjectileStates state, ProjectileTypes type, int angle) {
        
    switch (state) {
    case ProjectileStates::ALIVE:
        switch (type) {
        case ProjectileTypes::BazookaProj:
            bazooka_missile_an.update_with_angle(angle);
            break;
        case ProjectileTypes::MortarProj:
            mortar_round_an.update_with_angle(angle);
            break;
        case ProjectileTypes::AirStrikeProj:
            air_missile_an.update_with_angle(angle);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}