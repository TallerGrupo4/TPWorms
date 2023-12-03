#ifndef WORM_ANIMATIONS_H
#define WORM_ANIMATIONS_H

#include <memory>
#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"
#include "AnimationScroll.h"

class WormAnimations {
public:
    WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(int state, int angle, TOOLS weapon, int weapon_ammo, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       const bool facing_left,
                       int left_offset = 0,
                       int right_offset = 0,
                       int above_offset = 0,
                       int bellow_offset = 0);
    void update_from_snapshot(int state, int old_state, int angle, int old_angle, bool facing_left, bool old_facing_left, TOOLS weapon, int old_aiming_angle, int new_aiming_angle);
    void update_from_iter(int state, int angle, bool facing_left);
    void update_changing_weapons(TOOLS actual_weapon, TOOLS new_weapon, int actual_weapon_ammo, int new_weapon_ammo, int angle, const bool facing_left);
private:
    void reset_old_an(int old_state, int old_angle, bool old_facing_left, int old_aiming_angle);  
    bool is_action_state(int state);
    bool is_weapon_grenade_type(TOOLS weapon);
    void check_aiming_angle(AnimationScroll& an, int new_aiming_angle, int old_aiming_angle);
    void render_angle_dependent_an(Animation& up_an, Animation& down_an,
                                    const int angle, const bool facing_left,
                                    SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                    SDL_RendererFlip flip,
                                    int left_offset,
                                    int right_offset,
                                    int above_offset,
                                    int bellow_offset);
    void push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left);
    void push_drop_weapon_an(TOOLS weapon, int weapon_ammo, int angle, const bool facing_left);
    void push_pick_up_weapon_an(TOOLS weapon, int weapon_ammo, int angle, const bool facing_left);

    std::list<std::reference_wrapper<Animation>> lingering_animations;
    TOOLS old_weapon;
    /*WORM MOVEMENTS*/
    Animation still_0_an;
    Animation still_0_up_an;
    Animation still_0_down_an;
    //Animation still_1_an;
    Animation walking_an;
    Animation walking_up_an;
    Animation walking_down_an;
    Animation backflip_an;
    Animation jump_an;
    Animation jump_up_an;
    Animation jump_down_an;
    Animation fall_an;
    Animation slide_an;
    Animation slide_up_an;
    Animation slide_down_an;
    Animation dead_an;
    Animation winner_an;
    /*WORM STILL STANCE WEAPONS*/
    Animation still_baz_an;
    Animation still_baz_up_an;
    Animation still_baz_down_an;
    Animation still_mortar_an;
    Animation still_mortar_up_an;
    Animation still_mortar_down_an;
    Animation still_air_an;
    Animation still_air_up_an;
    Animation still_air_down_an;
    Animation still_tel_an;
    Animation still_tel_up_an;
    Animation still_tel_down_an;
    Animation still_thr_an;
    Animation still_thr_up_an;
    Animation still_thr_down_an;
    Animation still_grn_an;
    Animation still_grn_up_an;
    Animation still_grn_down_an;
    Animation still_cls_an;
    Animation still_cls_up_an;
    Animation still_cls_down_an;
    Animation still_ban_an;
    Animation still_ban_up_an;
    Animation still_ban_down_an;
    Animation still_hgr_an;
    Animation still_hgr_up_an;
    Animation still_hgr_down_an;
    Animation still_dyn_an;
    Animation still_dyn_up_an;
    Animation still_dyn_down_an;
    Animation still_bsb_an;
    Animation still_bsb_up_an;
    Animation still_bsb_down_an;
    /*WORM CHANGING WEAPONS*/
    Animation get_baz_an;
    Animation get_baz_up_an;
    Animation get_baz_down_an;
    Animation drop_baz_an;
    Animation drop_baz_up_an;
    Animation drop_baz_down_an;
    Animation get_mortar_an;
    Animation get_mortar_up_an;
    Animation get_mortar_down_an;
    Animation drop_mortar_an;
    Animation drop_mortar_up_an;
    Animation drop_mortar_down_an;
    Animation get_air_an;
    Animation get_air_up_an;
    Animation get_air_down_an;
    Animation drop_air_an;
    Animation drop_air_up_an;
    Animation drop_air_down_an;
    Animation get_tel_an;
    Animation get_tel_up_an;
    Animation get_tel_down_an;
    Animation drop_tel_an;
    Animation drop_tel_up_an;
    Animation drop_tel_down_an;
    Animation get_thr_an;
    Animation get_thr_up_an;
    Animation get_thr_down_an;
    Animation drop_thr_an;
    Animation drop_thr_up_an;
    Animation drop_thr_down_an;
    Animation get_grn_an;
    Animation get_grn_up_an;
    Animation get_grn_down_an;
    Animation drop_grn_an;
    Animation drop_grn_up_an;
    Animation drop_grn_down_an;
    Animation get_cls_an;
    Animation get_cls_up_an;
    Animation get_cls_down_an;
    Animation drop_cls_an;
    Animation drop_cls_up_an;
    Animation drop_cls_down_an;
    Animation get_ban_an;
    Animation get_ban_up_an;
    Animation get_ban_down_an;
    Animation drop_ban_an;
    Animation drop_ban_up_an;
    Animation drop_ban_down_an;
    Animation get_hgr_an;
    Animation get_hgr_up_an;
    Animation get_hgr_down_an;
    Animation drop_hgr_an;
    Animation drop_hgr_up_an;
    Animation drop_hgr_down_an;
    Animation get_dyn_an;
    Animation get_dyn_up_an;
    Animation get_dyn_down_an;
    Animation drop_dyn_an;
    Animation drop_dyn_up_an;
    Animation drop_dyn_down_an;
    Animation get_bsb_an;
    Animation get_bsb_up_an;
    Animation get_bsb_down_an;  
    Animation drop_bsb_an;
    Animation drop_bsb_up_an;
    Animation drop_bsb_down_an;
    /*WORM AIMING WEAPONS*/
    AnimationScroll aim_baz_an;
    AnimationScroll aim_baz_up_an;
    AnimationScroll aim_baz_down_an;
    AnimationScroll aim_mortar_an;
    AnimationScroll aim_mortar_up_an;
    AnimationScroll aim_mortar_down_an;
    AnimationScroll aim_thr_an;
    AnimationScroll aim_thr_up_an;
    AnimationScroll aim_thr_down_an;
    AnimationScroll aim_grn_an;
    AnimationScroll aim_grn_up_an;
    AnimationScroll aim_grn_down_an;
    AnimationScroll aim_cls_an;
    AnimationScroll aim_cls_up_an;
    AnimationScroll aim_cls_down_an;
    AnimationScroll aim_ban_an;
    AnimationScroll aim_ban_up_an;
    AnimationScroll aim_ban_down_an;
    AnimationScroll aim_hgr_an;
    AnimationScroll aim_hgr_up_an;
    AnimationScroll aim_hgr_down_an;
    AnimationScroll aim_bsb_an;
    AnimationScroll aim_bsb_up_an;
    AnimationScroll aim_bsb_down_an;
};

#endif  // WORM_ANIMATIONS_H