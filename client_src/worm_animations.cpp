#include "worm_animations.h"

WormAnimations::WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, int worm_state, int worm_angle, TOOLS weapon, int weapon_ammo, bool facing_left, int aiming_angle) :                                /*WORM PREVIOUS INFO*/
                                old_state(worm_state),
                                old_angle(worm_angle),
                                old_weapon(weapon),
                                old_weapon_ammo(weapon_ammo),
                                old_facing_left(facing_left),
                                old_aiming_angle(aiming_angle),
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
    
void WormAnimations::render_angle_dependent_an(Animation& an, Animation& up_an, Animation& down_an,
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
    } else {
        an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
    }
}

void WormAnimations::render_worm_still_with_weapon(TOOLS weapon, int weapon_ammo,
                    const int angle, const bool facing_left,
                    SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                    SDL_RendererFlip flip,
                    int left_offset,
                    int right_offset,
                    int above_offset,
                    int bellow_offset) {
    if(weapon_ammo == 0 and is_weapon_grenade_type(weapon)) {
        render_angle_dependent_an(still_thr_an, still_thr_up_an, still_thr_down_an,
                angle, facing_left,
                renderer, dst,
                flip,
                left_offset,
                right_offset,
                above_offset,
                bellow_offset);
        return;
    }
    switch (weapon) {
    case BAZOOKA:
        render_angle_dependent_an(still_baz_an, still_baz_up_an, still_baz_down_an,
                angle, facing_left,
                renderer, dst,
                flip,
                left_offset,
                right_offset,
                above_offset,
                bellow_offset);
        break;
    case MORTAR:
        render_angle_dependent_an(still_mortar_an, still_mortar_up_an, still_mortar_down_an,
                    angle, facing_left,
                    renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        break;
    case GREEN_GRENADE:
        render_angle_dependent_an(still_grn_an, still_grn_up_an, still_grn_down_an,
                        angle, facing_left,
                        renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case HOLY_GRENADE:
        render_angle_dependent_an(still_hgr_an, still_hgr_up_an, still_hgr_down_an,
                            angle, facing_left,
                            renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
        break;
    case DYNAMITE:
        render_angle_dependent_an(still_dyn_an, still_dyn_up_an, still_dyn_down_an,
                                angle, facing_left,
                                renderer, dst,
                                flip,
                                left_offset,
                                right_offset,
                                above_offset,
                                bellow_offset);
        break;
    case BASEBALL_BAT:
        render_angle_dependent_an(still_bsb_an, still_bsb_up_an, still_bsb_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        break;
    case RED_GRENADE:
        render_angle_dependent_an(still_cls_an, still_cls_up_an, still_cls_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
        break;
    case BANANA:
        render_angle_dependent_an(still_ban_an, still_ban_up_an, still_ban_down_an,
                                            angle, facing_left,
                                            renderer, dst,
                                            flip,
                                            left_offset,
                                            right_offset,
                                            above_offset,
                                            bellow_offset);
        break;
    case AIRSTRIKE:
        render_angle_dependent_an(still_air_an, still_air_up_an, still_air_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
        break;
    case TELEPORTATION:
        render_angle_dependent_an(still_tel_an, still_tel_up_an, still_tel_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
        break;
    case NO_TOOL:
        render_angle_dependent_an(still_0_an, still_0_up_an, still_0_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
        break;
    }
}

void WormAnimations::render(int state, int angle, TOOLS weapon, int weapon_ammo, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
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
        render_worm_still_with_weapon(weapon, weapon_ammo,
                        angle, facing_left,
                        renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case CLIMBING:
        if(angle > 0) {
            if (!facing_left) {
                walking_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                walking_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                walking_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                walking_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        }
        break;
    case JUMPING:
        render_angle_dependent_an(jump_an, jump_up_an, jump_down_an,
                                            angle, facing_left,
                                            renderer, dst,
                                            flip,
                                            left_offset,
                                            right_offset,
                                            above_offset,
                                            bellow_offset);
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
        render_angle_dependent_an(slide_an, slide_up_an, slide_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
        break;
    case AIMING:
        switch (weapon) {
        case BAZOOKA:
            render_angle_dependent_an(aim_baz_an, aim_baz_up_an, aim_baz_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
            break;
        case MORTAR:
            render_angle_dependent_an(aim_mortar_an, aim_mortar_up_an, aim_mortar_down_an,
                                                angle, facing_left,
                                                renderer, dst,
                                                flip,
                                                left_offset,
                                                right_offset,
                                                above_offset,
                                                bellow_offset);
            break;
        case GREEN_GRENADE:
            render_angle_dependent_an(aim_grn_an, aim_grn_up_an, aim_grn_down_an,
                                                    angle, facing_left,
                                                    renderer, dst,
                                                    flip,
                                                    left_offset,
                                                    right_offset,
                                                    above_offset,
                                                    bellow_offset);
            break;
        case HOLY_GRENADE:
            render_angle_dependent_an(aim_hgr_an, aim_hgr_up_an, aim_hgr_down_an,
                                                    angle, facing_left,
                                                    renderer, dst,
                                                    flip,
                                                    left_offset,
                                                    right_offset,
                                                    above_offset,
                                                    bellow_offset);
            break;
        case BASEBALL_BAT:
            render_angle_dependent_an(aim_bsb_an, aim_bsb_up_an, aim_bsb_down_an,
                                                    angle, facing_left,
                                                    renderer, dst,
                                                    flip,
                                                    left_offset,
                                                    right_offset,
                                                    above_offset,
                                                    bellow_offset);
            break;
        case RED_GRENADE:
            render_angle_dependent_an(aim_cls_an, aim_cls_up_an, aim_cls_down_an,
                                                    angle, facing_left,
                                                    renderer, dst,
                                                    flip,
                                                    left_offset,
                                                    right_offset,
                                                    above_offset,
                                                    bellow_offset);
            break;
        case BANANA:
            render_angle_dependent_an(aim_ban_an, aim_ban_up_an, aim_ban_down_an,
                                                    angle, facing_left,
                                                    renderer, dst,
                                                    flip,
                                                    left_offset,
                                                    right_offset,
                                                    above_offset,
                                                    bellow_offset);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void WormAnimations::reset_old_specific_an(Animation& an, Animation& up_an, Animation& down_an) {
    if(old_angle > 0) {
        if (!old_facing_left) {
            up_an.reset();
        } else {
            down_an.reset();
        }
    } else if (old_angle < 0) {
        if (!old_facing_left) {
            down_an.reset();
        } else {
            up_an.reset();
        }
    } else {
        an.reset();
    }
}

void WormAnimations::reset_old_an() {
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
        reset_old_specific_an(jump_an, jump_up_an, jump_down_an);
        break;
    case BACKFLIPPING:
        backflip_an.reset();
        break;
    default:
        break;
    }
}

void WormAnimations::update_animations(Animation& up_an, Animation& down_an, int angle, bool facing_left) {
    if(angle > 0) {
        if (!facing_left) {
            up_an.update_once();
        } else {
            down_an.update_once();
        }
    } else if (angle < 0) {
        if (!facing_left) {
            down_an.update_once();
        } else {
            up_an.update_once();
        }
    }
}

void WormAnimations::update_aiming_animations(AnimationScroll& an, AnimationScroll& up_an, AnimationScroll& down_an, int angle, bool facing_left, int aiming_angle, TOOLS weapon) {
    if(angle > 0) {
        if (!facing_left) {
            up_an.update_with_angle(aiming_angle);
        } else {
            down_an.update_with_angle(aiming_angle);
        }
    } else if (angle < 0) {
        if (!facing_left) {
            down_an.update_with_angle(aiming_angle);
        } else {
            up_an.update_with_angle(aiming_angle);
        }
    } else {
        an.update_with_angle(aiming_angle);
    }
}

void WormAnimations::update_from_snapshot(int state, int angle, bool facing_left, TOOLS weapon, int weapon_ammo, int aiming_angle) {
    if(state != old_state) {
        reset_old_an();
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
        update_animations(walking_up_an, walking_down_an, angle, facing_left);
        break;
    case JUMPING:
        if(angle == 0) {
            jump_an.update_once();
        } else {
            update_animations(jump_up_an, jump_down_an, angle, facing_left);
        }
        break;
    case BACKFLIPPING:
        backflip_an.update_once();
        break;
    case FALLING:
        walking_an.update_once();
        break;
    case SLIDING:
        if(angle == 0) {
            slide_an.update_once();
        } else {
            update_animations(slide_up_an, slide_down_an, angle, facing_left);
        }
        break;
    case AIMING:
        switch (weapon) {
        case BAZOOKA:
            update_aiming_animations(aim_baz_an, aim_baz_up_an, aim_baz_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case MORTAR:
            update_aiming_animations(aim_mortar_an, aim_mortar_up_an, aim_mortar_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case GREEN_GRENADE:
            update_aiming_animations(aim_grn_an, aim_grn_up_an, aim_grn_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case RED_GRENADE:
            update_aiming_animations(aim_cls_an, aim_cls_up_an, aim_cls_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case BANANA:
            update_aiming_animations(aim_ban_an, aim_ban_up_an, aim_ban_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case HOLY_GRENADE:
            update_aiming_animations(aim_hgr_an, aim_hgr_up_an, aim_hgr_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        case BASEBALL_BAT:
            update_aiming_animations(aim_bsb_an, aim_bsb_up_an, aim_bsb_down_an, angle, facing_left, aiming_angle, weapon);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    old_state = state;
    old_angle = angle;
    old_facing_left = facing_left;
    old_aiming_angle = aiming_angle;
    old_weapon = weapon;
    old_weapon_ammo = weapon_ammo;
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
        if(angle == 0) {
            still_0_an.update_once();
        } else {
            update_animations(still_0_up_an, still_0_down_an, angle, facing_left);
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

void WormAnimations::push_drop_weapon_an(int angle, const bool facing_left) {
    if(old_weapon_ammo == 0 and is_weapon_grenade_type(old_weapon)) {
        push_back_with_angle(drop_thr_an, drop_thr_down_an, drop_thr_up_an, angle, facing_left);
        return;
    }
    switch (old_weapon) {
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

void WormAnimations::push_pick_up_weapon_an(TOOLS weapon, int weapon_ammo, int angle, const bool facing_left) {
    if(weapon_ammo == 0 and is_weapon_grenade_type(weapon)) {
        push_back_with_angle(get_thr_an, get_thr_down_an, get_thr_up_an, angle, facing_left);
        return;
    }
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

void WormAnimations::update_changing_weapons(TOOLS new_weapon, int new_weapon_ammo, int angle, const bool facing_left) {
    push_drop_weapon_an(angle, facing_left);
    push_pick_up_weapon_an(new_weapon, new_weapon_ammo, angle, facing_left);
}

bool WormAnimations::is_action_state(int state) {
    return (state == MOVING or state == CLIMBING or 
            state == JUMPING or state == SLIDING or 
            state == BACKFLIPPING or state == FALLING or
            state == AIMING or state == SHOOTED);

}

bool WormAnimations::is_weapon_grenade_type(TOOLS weapon) {
    return (weapon == TOOLS::GREEN_GRENADE or weapon == TOOLS::RED_GRENADE or
            weapon == TOOLS::BANANA or weapon == TOOLS::HOLY_GRENADE or
            weapon == TOOLS::DYNAMITE);

}
