#include "provision_box_animations.h"

ProvisionBoxAnimations::ProvisionBoxAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces) :
    trap_box_disguise(static_cast<BoxType>(0)),
    mcrate_still_an(renderer, surfaces.mcrate_still, SECS_FOR_PROVISION_BOXES_SPRITES, false, true),
    mcrate_picked_an(renderer, surfaces.mcrate_picked, SECS_FOR_PROVISION_BOXES_SPRITES, true),
    wcrate_still_an(renderer, surfaces.wcrate_still, SECS_FOR_PROVISION_BOXES_SPRITES, false, true),
    wcrate_picked_an(renderer, surfaces.wcrate_picked, SECS_FOR_PROVISION_BOXES_SPRITES, true) {
        trap_box_disguise = static_cast<BoxType>(rand() % PROVISION_BOX_DISGUISE_TYPES);
}

void ProvisionBoxAnimations::render(BoxState state, BoxType type, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                    int left_offset,
                    int right_offset,
                    int above_offset,
                    int bellow_offset) {
    
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    switch (state) {
        case BoxState::UNPICKED:
            switch (type) {
                case BoxType::HEALTH_BOX:
                    mcrate_still_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                    break;
                case BoxType::AMMO_BOX:
                    wcrate_still_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                    break;
                case BoxType::TRAP_BOX:
                    switch (trap_box_disguise) {
                        case BoxType::HEALTH_BOX:
                            mcrate_still_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                            break;
                        case BoxType::AMMO_BOX:
                            wcrate_still_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                            break;
                        default:
                            break;
                    }
                    break;
            }
        case BoxState::PICKED:
            switch (type) {
                case BoxType::HEALTH_BOX:
                    mcrate_picked_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                    break;
                case BoxType::AMMO_BOX:
                    wcrate_picked_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                    break;
                case BoxType::TRAP_BOX:
                    switch (trap_box_disguise) {
                        case BoxType::HEALTH_BOX:
                            mcrate_picked_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                            break;
                        case BoxType::AMMO_BOX:
                            wcrate_picked_an.render(renderer, dst, flip, left_offset, right_offset, above_offset, bellow_offset);
                            break;
                        default:
                            break;
                    }
                    break;
            }
            break;
    }

}

void ProvisionBoxAnimations::update_from_iter(BoxState state, BoxType type) {
    switch (state) {
        case BoxState::UNPICKED:
            switch (type) {
                case BoxType::HEALTH_BOX:
                    mcrate_still_an.update_once();
                    break;
                case BoxType::AMMO_BOX:
                    wcrate_still_an.update_once();
                    break;
                case BoxType::TRAP_BOX:
                    switch (trap_box_disguise) {
                        case BoxType::HEALTH_BOX:
                            mcrate_still_an.update_once();
                            break;
                        case BoxType::AMMO_BOX:
                            wcrate_still_an.update_once();
                            break;
                        default:
                            break;
                    }
                    break;
            }
        case BoxState::PICKED:
            switch (type) {
                case BoxType::HEALTH_BOX:
                    mcrate_picked_an.update_once();
                    break;
                case BoxType::AMMO_BOX:
                    wcrate_picked_an.update_once();
                    break;
                case BoxType::TRAP_BOX:
                    switch (trap_box_disguise) {
                        case BoxType::HEALTH_BOX:
                            mcrate_picked_an.update_once();
                            break;
                        case BoxType::AMMO_BOX:
                            wcrate_picked_an.update_once();
                            break;
                        default:
                            break;
                    }
                    break;
            }
            break;
    }
}
