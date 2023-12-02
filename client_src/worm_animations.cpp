#include "worm_animations.h"

WormAnimations::WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces) :
                                old_weapon(TOOLS::NO_TOOL),
                                /*WORM MOVEMENTS*/
                                still_0_an(renderer, surfaces.still_0_worm, SECS_FOR_STILL_SPRITES),
                                still_0_up_an(renderer, surfaces.still_0_up_worm, SECS_FOR_STILL_SPRITES),
                                still_0_down_an(renderer, surfaces.still_0_down_worm, SECS_FOR_STILL_SPRITES),
                                //still_1_an(renderer, surfaces.still_1_worm, SECS_FOR_STILL_1_SPRITES),
                                walking_an(renderer, surfaces.walking_worm, SECS_FOR_WALKING_SPRITES),
                                walking_up_an(renderer, surfaces.walking_up_worm, SECS_FOR_WALKING_SPRITES),
                                walking_down_an(renderer, surfaces.walking_down_worm, SECS_FOR_WALKING_SPRITES),
                                backflip_an(renderer, surfaces.backflip_worm, SECS_FOR_BACKFLIP_SPRITES),
                                jump_an(renderer, surfaces.jump_worm, SECS_FOR_JUMP_SPRITES),
                                jump_up_an(renderer, surfaces.jump_up_worm, SECS_FOR_JUMP_SPRITES),
                                jump_down_an(renderer, surfaces.jump_down_worm, SECS_FOR_JUMP_SPRITES),
                                fall_an(renderer, surfaces.fall_worm, SECS_FOR_FALL_SPRITES),
                                slide_an(renderer, surfaces.slide_worm, SECS_FOR_SLIDE_SPRITES),
                                slide_up_an(renderer, surfaces.slide_up_worm, SECS_FOR_SLIDE_SPRITES),
                                slide_down_an(renderer, surfaces.slide_down_worm, SECS_FOR_SLIDE_SPRITES),
                                dead_an(renderer, surfaces.dead_worm, SECS_FOR_DEAD_SPRITES, false, true),
                                winner_an(renderer, surfaces.winner_worm, SECS_FOR_WIN_SPRITES),
                                /*WORM STILL STANCE WEAPONS*/
                                still_baz_an(renderer, surfaces.still_baz_worm, SECS_FOR_STILL_SPRITES),
                                still_baz_up_an(renderer, surfaces.still_baz_up_worm, SECS_FOR_STILL_SPRITES),
                                still_baz_down_an(renderer, surfaces.still_baz_down_worm, SECS_FOR_STILL_SPRITES),
                                still_mortar_an(renderer, surfaces.still_mortar_worm, SECS_FOR_STILL_SPRITES),
                                still_mortar_up_an(renderer, surfaces.still_mortar_up_worm, SECS_FOR_STILL_SPRITES),
                                still_mortar_down_an(renderer, surfaces.still_mortar_down_worm, SECS_FOR_STILL_SPRITES),
                                still_air_an(renderer, surfaces.still_air_worm, SECS_FOR_STILL_SPRITES),
                                still_air_up_an(renderer, surfaces.still_air_up_worm, SECS_FOR_STILL_SPRITES),
                                still_air_down_an(renderer, surfaces.still_air_down_worm, SECS_FOR_STILL_SPRITES),
                                still_tel_an(renderer, surfaces.still_tel_worm, SECS_FOR_STILL_SPRITES),
                                still_tel_up_an(renderer, surfaces.still_tel_up_worm, SECS_FOR_STILL_SPRITES),
                                still_tel_down_an(renderer, surfaces.still_tel_down_worm, SECS_FOR_STILL_SPRITES),
                                still_thr_an(renderer, surfaces.still_thr_worm, SECS_FOR_STILL_SPRITES),
                                still_thr_up_an(renderer, surfaces.still_thr_up_worm, SECS_FOR_STILL_SPRITES),
                                still_thr_down_an(renderer, surfaces.still_thr_down_worm, SECS_FOR_STILL_SPRITES),
                                still_grn_an(renderer, surfaces.still_grn_worm, SECS_FOR_STILL_SPRITES),
                                still_grn_up_an(renderer, surfaces.still_grn_up_worm, SECS_FOR_STILL_SPRITES),
                                still_grn_down_an(renderer, surfaces.still_grn_down_worm, SECS_FOR_STILL_SPRITES),
                                still_cls_an(renderer, surfaces.still_cls_worm, SECS_FOR_STILL_SPRITES),
                                still_cls_up_an(renderer, surfaces.still_cls_up_worm, SECS_FOR_STILL_SPRITES),
                                still_cls_down_an(renderer, surfaces.still_cls_down_worm, SECS_FOR_STILL_SPRITES),
                                still_ban_an(renderer, surfaces.still_ban_worm, SECS_FOR_STILL_SPRITES),
                                still_ban_up_an(renderer, surfaces.still_ban_up_worm, SECS_FOR_STILL_SPRITES),
                                still_ban_down_an(renderer, surfaces.still_ban_down_worm, SECS_FOR_STILL_SPRITES),
                                still_hgr_an(renderer, surfaces.still_hgr_worm, SECS_FOR_STILL_SPRITES),
                                still_hgr_up_an(renderer, surfaces.still_hgr_up_worm, SECS_FOR_STILL_SPRITES),
                                still_hgr_down_an(renderer, surfaces.still_hgr_down_worm, SECS_FOR_STILL_SPRITES),
                                still_dyn_an(renderer, surfaces.still_dyn_worm, SECS_FOR_STILL_SPRITES),
                                still_dyn_up_an(renderer, surfaces.still_dyn_up_worm, SECS_FOR_STILL_SPRITES),
                                still_dyn_down_an(renderer, surfaces.still_dyn_down_worm, SECS_FOR_STILL_SPRITES),
                                still_bsb_an(renderer, surfaces.still_bsb_worm, SECS_FOR_STILL_SPRITES),
                                still_bsb_up_an(renderer, surfaces.still_bsb_up_worm, SECS_FOR_STILL_SPRITES),
                                still_bsb_down_an(renderer, surfaces.still_bsb_down_worm, SECS_FOR_STILL_SPRITES),
                                /*WORM CHANGING WEAPONS*/
                                get_baz_an(renderer, surfaces.get_baz_worm, SECS_FOR_STILL_SPRITES, true),
                                get_baz_up_an(renderer, surfaces.get_baz_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_baz_down_an(renderer, surfaces.get_baz_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_an(renderer, surfaces.drop_baz_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_up_an(renderer, surfaces.drop_baz_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_down_an(renderer, surfaces.drop_baz_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_mortar_an(renderer, surfaces.get_mortar_worm, SECS_FOR_STILL_SPRITES, true),
                                get_mortar_up_an(renderer, surfaces.get_mortar_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_mortar_down_an(renderer, surfaces.get_mortar_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_mortar_an(renderer, surfaces.drop_mortar_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_mortar_up_an(renderer, surfaces.drop_mortar_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_mortar_down_an(renderer, surfaces.drop_mortar_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_air_an(renderer, surfaces.get_air_worm, SECS_FOR_STILL_SPRITES, true),
                                get_air_up_an(renderer, surfaces.get_air_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_air_down_an(renderer, surfaces.get_air_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_air_an(renderer, surfaces.drop_air_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_air_up_an(renderer, surfaces.drop_air_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_air_down_an(renderer, surfaces.drop_air_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_tel_an(renderer, surfaces.get_tel_worm, SECS_FOR_STILL_SPRITES, true),
                                get_tel_up_an(renderer, surfaces.get_tel_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_tel_down_an(renderer, surfaces.get_tel_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_tel_an(renderer, surfaces.drop_tel_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_tel_up_an(renderer, surfaces.drop_tel_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_tel_down_an(renderer, surfaces.drop_tel_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_thr_an(renderer, surfaces.get_thr_worm, SECS_FOR_STILL_SPRITES, true),
                                get_thr_up_an(renderer, surfaces.get_thr_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_thr_down_an(renderer, surfaces.get_thr_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_thr_an(renderer, surfaces.drop_thr_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_thr_up_an(renderer, surfaces.drop_thr_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_thr_down_an(renderer, surfaces.drop_thr_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_grn_an(renderer, surfaces.get_grn_worm, SECS_FOR_STILL_SPRITES, true),
                                get_grn_up_an(renderer, surfaces.get_grn_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_grn_down_an(renderer, surfaces.get_grn_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_grn_an(renderer, surfaces.drop_grn_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_grn_up_an(renderer, surfaces.drop_grn_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_grn_down_an(renderer, surfaces.drop_grn_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_cls_an(renderer, surfaces.get_cls_worm, SECS_FOR_STILL_SPRITES, true),
                                get_cls_up_an(renderer, surfaces.get_cls_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_cls_down_an(renderer, surfaces.get_cls_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_cls_an(renderer, surfaces.drop_cls_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_cls_up_an(renderer, surfaces.drop_cls_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_cls_down_an(renderer, surfaces.drop_cls_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_ban_an(renderer, surfaces.get_ban_worm, SECS_FOR_STILL_SPRITES, true),
                                get_ban_up_an(renderer, surfaces.get_ban_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_ban_down_an(renderer, surfaces.get_ban_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_ban_an(renderer, surfaces.drop_ban_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_ban_up_an(renderer, surfaces.drop_ban_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_ban_down_an(renderer, surfaces.drop_ban_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_hgr_an(renderer, surfaces.get_hgr_worm, SECS_FOR_STILL_SPRITES, true),
                                get_hgr_up_an(renderer, surfaces.get_hgr_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_hgr_down_an(renderer, surfaces.get_hgr_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_hgr_an(renderer, surfaces.drop_hgr_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_hgr_up_an(renderer, surfaces.drop_hgr_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_hgr_down_an(renderer, surfaces.drop_hgr_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_dyn_an(renderer, surfaces.get_dyn_worm, SECS_FOR_STILL_SPRITES, true),
                                get_dyn_up_an(renderer, surfaces.get_dyn_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_dyn_down_an(renderer, surfaces.get_dyn_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_dyn_an(renderer, surfaces.drop_dyn_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_dyn_up_an(renderer, surfaces.drop_dyn_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_dyn_down_an(renderer, surfaces.drop_dyn_down_worm, SECS_FOR_STILL_SPRITES, true),
                                get_bsb_an(renderer, surfaces.get_bsb_worm, SECS_FOR_STILL_SPRITES, true),
                                get_bsb_up_an(renderer, surfaces.get_bsb_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_bsb_down_an(renderer, surfaces.get_bsb_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_bsb_an(renderer, surfaces.drop_bsb_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_bsb_up_an(renderer, surfaces.drop_bsb_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_bsb_down_an(renderer, surfaces.drop_bsb_down_worm, SECS_FOR_STILL_SPRITES, true),
                                /*WORM AIMING WEAPONS*/
                                aim_baz_an(renderer, surfaces.aim_baz_worm, SECS_FOR_STILL_SPRITES),
                                aim_baz_up_an(renderer, surfaces.aim_baz_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_baz_down_an(renderer, surfaces.aim_baz_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_mortar_an(renderer, surfaces.aim_mortar_worm, SECS_FOR_STILL_SPRITES),
                                aim_mortar_up_an(renderer, surfaces.aim_mortar_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_mortar_down_an(renderer, surfaces.aim_mortar_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_thr_an(renderer, surfaces.aim_thr_worm, SECS_FOR_STILL_SPRITES),
                                aim_thr_up_an(renderer, surfaces.aim_thr_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_thr_down_an(renderer, surfaces.aim_thr_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_grn_an(renderer, surfaces.aim_grn_worm, SECS_FOR_STILL_SPRITES),
                                aim_grn_up_an(renderer, surfaces.aim_grn_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_grn_down_an(renderer, surfaces.aim_grn_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_cls_an(renderer, surfaces.aim_cls_worm, SECS_FOR_STILL_SPRITES),
                                aim_cls_up_an(renderer, surfaces.aim_cls_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_cls_down_an(renderer, surfaces.aim_cls_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_ban_an(renderer, surfaces.aim_ban_worm, SECS_FOR_STILL_SPRITES),
                                aim_ban_up_an(renderer, surfaces.aim_ban_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_ban_down_an(renderer, surfaces.aim_ban_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_hgr_an(renderer, surfaces.aim_hgr_worm, SECS_FOR_STILL_SPRITES),
                                aim_hgr_up_an(renderer, surfaces.aim_hgr_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_hgr_down_an(renderer, surfaces.aim_hgr_down_worm, SECS_FOR_STILL_SPRITES),
                                aim_bsb_an(renderer, surfaces.aim_bsb_worm, SECS_FOR_STILL_SPRITES),
                                aim_bsb_up_an(renderer, surfaces.aim_bsb_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_bsb_down_an(renderer, surfaces.aim_bsb_down_worm, SECS_FOR_STILL_SPRITES) {

}
    
void WormAnimations::render_angle_dependent_an(Animation& up_an, Animation& down_an,
                                               const int angle, const bool facing_left,
                                               SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                               SDL_RendererFlip flip,
                                               int left_offset,
                                               int right_offset,
                                               int above_offset,
                                               int bellow_offset) {
    if(angle > 0) {
        if (!facing_left) {
            up_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        } else {
            down_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        }
    } else if (angle < 0) {
        if (!facing_left) {
            down_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        } else {
            up_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        }
    }
}

void WormAnimations::render(int state, int angle, TOOLS weapon, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                    const bool facing_left,
                    int left_offset,
                    int right_offset,
                    int above_offset,
                    int bellow_offset) {       
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if(!lingering_animations.empty()) {
        lingering_animations.front().get().render(renderer, dst,
                                            flip,
                                            left_offset,
                                            right_offset,
                                            above_offset,
                                            bellow_offset);
        return;
    }
    
    switch (state) {
    case MOVING:
        walking_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case DEAD:
        dead_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset-5,
                        above_offset-12,
                        bellow_offset+10);
        break;
    case WINNER:
        winner_an.render(renderer, dst,
                        flip,
                        left_offset-7,
                        right_offset,
                        above_offset-12,
                        bellow_offset);
        break;
    case STILL:
        switch (weapon) {
        case BAZOOKA:
            if(angle == 0) {
                still_baz_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_baz_up_an, still_baz_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case MORTAR:
            if(angle == 0) {
                still_mortar_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_mortar_up_an, still_mortar_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case GREEN_GRENADE:
            if(angle == 0) {
                still_grn_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_grn_up_an, still_grn_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case HOLY_GRENADE:
            if(angle == 0) {
                still_hgr_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_hgr_up_an, still_hgr_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case DYNAMITE:
            if(angle == 0) {
                still_dyn_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_dyn_up_an, still_dyn_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case BASEBALL_BAT:
            if(angle == 0) {
                still_bsb_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_bsb_up_an, still_bsb_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case RED_GRENADE:
            if(angle == 0) {
                still_cls_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_cls_up_an, still_cls_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case BANANA:
            if(angle == 0) {
                still_ban_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_ban_up_an, still_ban_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case AIRSTRIKE:
            if(angle == 0) {
                still_air_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_air_up_an, still_air_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case TELEPORTATION:
            if(angle == 0) {
                still_tel_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_tel_up_an, still_tel_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case NO_TOOL:
            if(angle == 0) {
                still_0_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_0_up_an, still_0_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        }
        break;
    case CLIMBING:
        render_angle_dependent_an(walking_up_an, walking_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        break;
    case JUMPING:
        if(angle == 0) {
            jump_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        } else {
            render_angle_dependent_an(jump_up_an, jump_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        }
        break;
    case BACKFLIPPING:
        backflip_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case FALLING:
        fall_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case SLIDING:
        if(angle == 0) {
            slide_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        } else {
            render_angle_dependent_an(slide_up_an, slide_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        }
        break;
    case AIMING:
        switch (weapon) {
        case BAZOOKA:
            if(angle == 0) {
                aim_baz_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_baz_up_an, aim_baz_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case MORTAR:
            if(angle == 0) {
                aim_mortar_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_mortar_up_an, aim_mortar_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case GREEN_GRENADE:
            if(angle == 0) {
                aim_grn_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_grn_up_an, aim_grn_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case HOLY_GRENADE:
            if(angle == 0) {
                aim_hgr_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_hgr_up_an, aim_hgr_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case BASEBALL_BAT:
            if(angle == 0) {
                aim_bsb_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_bsb_up_an, aim_bsb_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case RED_GRENADE:
            if(angle == 0) {
                aim_cls_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_cls_up_an, aim_cls_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        case BANANA:
            if(angle == 0) {
                aim_ban_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_ban_up_an, aim_ban_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset); 
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void WormAnimations::reset_old_an(int old_state, int old_angle, bool old_facing_left, int old_aiming_angle) {
    switch (old_state) {
    case MOVING:
        walking_an.reset();
        break;
    case CLIMBING:
        if(old_angle > 0) {
            if (!old_facing_left) {
                walking_up_an.reset();
            } else {
                walking_down_an.reset();
            }
        } else if (old_angle < 0) {
            if (!old_facing_left) {
                walking_down_an.reset();
            } else {
                walking_up_an.reset();
            }
        }
        break;
    case JUMPING:
        if(old_angle > 0) {
            if (!old_facing_left) {
                jump_up_an.reset();
            } else {
                jump_down_an.reset();
            }
        } else if (old_angle < 0) {
            if (!old_facing_left) {
                jump_down_an.reset();
            } else {
                jump_up_an.reset();
            }
        } else {
            jump_an.reset();
        }
        break;
    case BACKFLIPPING:
        backflip_an.reset();
        break;
    case AIMING:
        switch (old_weapon) {
            case BAZOOKA:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_baz_up_an.reset();
                    } else {
                        aim_baz_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_baz_down_an.reset();
                    } else {
                        aim_baz_up_an.reset();
                    }
                } else {
                    aim_baz_an.reset();
                }
                break;
            case MORTAR:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_mortar_up_an.reset();
                    } else {
                        aim_mortar_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_mortar_down_an.reset();
                    } else {
                        aim_mortar_up_an.reset();
                    }
                } else {
                    aim_mortar_an.reset();
                }
                break;
            case GREEN_GRENADE:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_grn_up_an.reset();
                    } else {
                        aim_grn_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_grn_down_an.reset();
                    } else {
                        aim_grn_up_an.reset();
                    }
                } else {
                    aim_grn_an.reset();
                }
                break;
            case RED_GRENADE:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_cls_up_an.reset();
                    } else {
                        aim_cls_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_cls_down_an.reset();
                    } else {
                        aim_cls_up_an.reset();
                    }
                } else {
                    aim_cls_an.reset();
                }
                break;
            case BANANA:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_ban_up_an.reset();
                    } else {
                        aim_ban_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_ban_down_an.reset();
                    } else {
                        aim_ban_up_an.reset();
                    }
                } else {
                    aim_ban_an.reset();
                }
                break;
            case HOLY_GRENADE:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_hgr_up_an.reset();
                    } else {
                        aim_hgr_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_hgr_down_an.reset();
                    } else {
                        aim_hgr_up_an.reset();
                    }
                } else {
                    aim_hgr_an.reset();
                }
                break;
            case BASEBALL_BAT:
                if(old_angle > 0) {
                    if (!old_facing_left) {
                        aim_bsb_up_an.reset();
                    } else {
                        aim_bsb_down_an.reset();
                    }
                } else if (old_angle < 0) {
                    if (!old_facing_left) {
                        aim_bsb_down_an.reset();
                    } else {
                        aim_bsb_up_an.reset();
                    }
                } else {
                    aim_bsb_an.reset();
                }
                break;
            default:
                break;
        }
        break;
    default:
        break;
    }
}

void WormAnimations::update_from_snapshot(int state, int old_state, int angle, int old_angle, bool facing_left, bool old_facing_left, TOOLS weapon, int old_aiming_angle, int new_aiming_angle) {
    if(state != old_state) {
        reset_old_an(old_state, old_angle, old_facing_left, old_aiming_angle);
    }
    if((is_action_state(state)) and (!lingering_animations.empty())) {
        for (auto& an : lingering_animations) {
            an.get().reset();
        }
        lingering_animations.clear();
    }
    switch (state) {
    case MOVING:
        walking_an.update_once();
        break;
    
    case CLIMBING:
        if(angle > 0) {
            if (!facing_left) {
                walking_up_an.update_once();
            } else {
                walking_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                walking_down_an.update_once();
            } else {
                walking_up_an.update_once();
            }
        }
        break;
    case JUMPING:
        if(angle > 0) {
            if (!facing_left) {
                jump_up_an.update_once();
            } else {
                jump_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                jump_down_an.update_once();
            } else {
                jump_up_an.update_once();
            }
        } else {
            jump_an.update_once();
        }
        break;
    case BACKFLIPPING:
        backflip_an.update_once();
        break;
    case FALLING:
        walking_an.update_once();
        break;
    case SLIDING:
        if(angle > 0) {
            if (!facing_left) {
                slide_up_an.update_once();
            } else {
                slide_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                slide_down_an.update_once();
            } else {
                slide_up_an.update_once();
            }
        } else {
            slide_an.update_once();
        }
        break;
    case AIMING:
        // std::cout << "ENTRE al AIMING del update from snapshot, new_aiming_angle: " << new_aiming_angle << " old_aiming_angle: " << old_aiming_angle << std::endl;
        switch (weapon) {
        case BAZOOKA:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_baz_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_baz_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_baz_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_baz_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_baz_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case MORTAR:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_mortar_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_mortar_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_mortar_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_mortar_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_mortar_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case GREEN_GRENADE:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_grn_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_grn_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_grn_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_grn_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_grn_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case RED_GRENADE:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_cls_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_cls_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_cls_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_cls_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_cls_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case BANANA:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_ban_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_ban_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_ban_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_ban_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_ban_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case HOLY_GRENADE:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_hgr_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_hgr_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_hgr_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_hgr_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_hgr_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        case BASEBALL_BAT:
            if(angle > 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_bsb_up_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_bsb_down_an, new_aiming_angle, old_aiming_angle);
                }
            } else if (angle < 0) {
                if (!facing_left) {
                    check_aiming_angle(aim_bsb_down_an, new_aiming_angle, old_aiming_angle);
                } else {
                    check_aiming_angle(aim_bsb_up_an, new_aiming_angle, old_aiming_angle);
                }
            } else {
                check_aiming_angle(aim_bsb_an, new_aiming_angle, old_aiming_angle);
            }
            old_weapon = weapon;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void WormAnimations::check_aiming_angle(AnimationScroll& an, int new_aiming_angle, int old_aiming_angle) {
    if(new_aiming_angle > old_aiming_angle) {
        an.update_once_down();
    } else if (new_aiming_angle < old_aiming_angle) {
        an.update_once_up();
    }
}

void WormAnimations::update_from_iter(int state, int angle, bool facing_left) {
    if((!is_action_state(state)) and (!lingering_animations.empty())) {
        if(!(lingering_animations.front().get().update_once())) {
            lingering_animations.front().get().reset();
            lingering_animations.pop_front();
        }
        return;
    }

    switch (state) {
    case STILL:
        if(angle > 0) {
            if (!facing_left) {
                still_0_up_an.update_once();
            } else {
                still_0_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                still_0_down_an.update_once();
            } else {
                still_0_up_an.update_once();
            }
        } else {
            still_0_an.update_once();
        }
        break;
    case DEAD:
        dead_an.update_once();
        break;
    case WINNER:
        winner_an.update_once();
        break;
    default:
        break;
    }
}

void WormAnimations::push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left) {
    if(angle > 0) {
        if (!facing_left) {
            lingering_animations.push_back(up_an);
        } else {
            lingering_animations.push_back(down_an);
        }
    } else if (angle < 0) {
        if (!facing_left) {
            lingering_animations.push_back(down_an);
        } else {
            lingering_animations.push_back(up_an);
        }
    } else {
        lingering_animations.push_back(middle_an);
    }
}

void WormAnimations::push_drop_weapon_an(TOOLS weapon, int angle, const bool facing_left) {
    switch (weapon) {
        case BAZOOKA:
            push_back_with_angle(drop_baz_an, drop_baz_down_an, drop_baz_up_an, angle, facing_left);
            break;
        case MORTAR:
            push_back_with_angle(drop_mortar_an, drop_mortar_down_an, drop_mortar_up_an, angle, facing_left);
            break;
        case GREEN_GRENADE:
            push_back_with_angle(drop_grn_an, drop_grn_down_an, drop_grn_up_an, angle, facing_left);
            break;
        case HOLY_GRENADE:
            push_back_with_angle(drop_hgr_an, drop_hgr_down_an, drop_hgr_up_an, angle, facing_left);
            break;
        case DYNAMITE:
            push_back_with_angle(drop_dyn_an, drop_dyn_down_an, drop_dyn_up_an, angle, facing_left);
            break;
        case BASEBALL_BAT:
            push_back_with_angle(drop_bsb_an, drop_bsb_down_an, drop_bsb_up_an, angle, facing_left);
            break;
        case RED_GRENADE:
            push_back_with_angle(drop_cls_an, drop_cls_down_an, drop_cls_up_an, angle, facing_left);
            break;
        case BANANA:
            push_back_with_angle(drop_ban_an, drop_ban_down_an, drop_ban_up_an, angle, facing_left);
            break;
        case AIRSTRIKE:
            push_back_with_angle(drop_air_an, drop_air_down_an, drop_air_up_an, angle, facing_left);
            break;
        case TELEPORTATION:
            push_back_with_angle(drop_tel_an, drop_tel_down_an, drop_tel_up_an, angle, facing_left);
            break;
        case NO_TOOL:
            break;
    }
}

void WormAnimations::push_pick_up_weapon_an(TOOLS weapon, int angle, const bool facing_left) {
    switch (weapon) {
        case BAZOOKA:
            push_back_with_angle(get_baz_an, get_baz_down_an, get_baz_up_an, angle, facing_left);
            break;
        case MORTAR:
            push_back_with_angle(get_mortar_an, get_mortar_down_an, get_mortar_up_an, angle, facing_left);
            break;
        case GREEN_GRENADE:
            push_back_with_angle(get_grn_an, get_grn_down_an, get_grn_up_an, angle, facing_left);
            break;
        case HOLY_GRENADE:
            push_back_with_angle(get_hgr_an, get_hgr_down_an, get_hgr_up_an, angle, facing_left);
            break;
        case DYNAMITE:
            push_back_with_angle(get_dyn_an, get_dyn_down_an, get_dyn_up_an, angle, facing_left);
            break;
        case BASEBALL_BAT:
            push_back_with_angle(get_bsb_an, get_bsb_down_an, get_bsb_up_an, angle, facing_left);
            break;
        case RED_GRENADE:
            push_back_with_angle(get_cls_an, get_cls_down_an, get_cls_up_an, angle, facing_left);
            break;
        case BANANA:
            push_back_with_angle(get_ban_an, get_ban_down_an, get_ban_up_an, angle, facing_left);
            break;
        case AIRSTRIKE:
            push_back_with_angle(get_air_an, get_air_down_an, get_air_up_an, angle, facing_left);
            break;
        case TELEPORTATION:
            push_back_with_angle(get_tel_an, get_tel_down_an, get_tel_up_an, angle, facing_left);
            break;
        case NO_TOOL:
            break;
    }
}

void WormAnimations::update_changing_weapons(TOOLS actual_weapon, TOOLS new_weapon, int angle, const bool facing_left) {
    push_drop_weapon_an(actual_weapon, angle, facing_left);
    push_pick_up_weapon_an(new_weapon, angle, facing_left);
}

bool WormAnimations::is_action_state(int state) {
    bool is_moving_state = (state == MOVING);
    bool is_climbing_state = (state == CLIMBING);
    bool is_jumping_state = (state == JUMPING);
    bool is_sliding_state = (state == SLIDING);
    bool is_backflipping_state = (state == BACKFLIPPING);
    bool is_falling_state = (state == FALLING);
    bool is_aiming_state = (state == AIMING);
    bool is_shooting_state = (state == SHOOTED);
    return (is_moving_state or is_climbing_state or is_jumping_state or is_sliding_state or is_backflipping_state or is_falling_state or is_aiming_state or is_shooting_state);
}
