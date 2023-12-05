#ifndef WORM_ANIMATIONS_H
#define WORM_ANIMATIONS_H

#include <list>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

#include "Animation.h"
#include "AnimationScroll.h"
#include "client_constants.h"
#include "surfaces.h"

// Class that represents the animations of a worm
class WormAnimations {
public:
    /**
     * @brief Construct a new Worm Animations object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     * @param worm_state Initial state of the worm
     * @param worm_angle Initial angle of the worm
     * @param weapon Initial weapon of the worm
     * @param weapon_ammo Initial ammo of the weapon of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param aiming_angle Initial angle of the aiming of the worm
     */
    WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, int worm_state,
                   int worm_angle, TOOLS weapon, int weapon_ammo, bool facing_left,
                   int aiming_angle);
    /**
     * @brief Renders the worm with the animation
     * @param state State of the worm
     * @param angle Angle of the worm
     * @param weapon Weapon of the worm
     * @param weapon_ammo Ammo of the weapon of the worm
     * @param renderer Renderer of the match
     * @param dst Destination rectangle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param left_offset Offset of the worm in the left side
     * @param right_offset Offset of the worm in the right side
     * @param above_offset Offset of the worm in the top side
     * @param bellow_offset Offset of the worm in the bottom side
     */
    void render(int state, int angle, TOOLS weapon, int weapon_ammo, SDL2pp::Renderer& renderer,
                const SDL2pp::Rect dst, const bool facing_left, int left_offset = 0,
                int right_offset = 0, int above_offset = 0, int bellow_offset = 0);
    /**
     * @brief Updates the worm from a snapshot received from the server
     * @param state State of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param weapon Weapon of the worm
     * @param weapon_ammo Ammo of the weapon of the worm
     * @param aiming_angle Angle of the aiming of the worm
     */
    void update_from_snapshot(int state, int angle, bool facing_left, TOOLS weapon, int weapon_ammo,
                              int aiming_angle);
    /**
     * @brief Updates the worm from the ticks of the match
     * @param state State of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     */
    void update_from_iter(int state, int angle, bool facing_left);
    /**
     * @brief Updates the changing weapons animations of the worm
     * @param new_weapon New weapon of the worm
     * @param new_weapon_ammo New ammo of the weapon of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     */
    void update_changing_weapons(TOOLS new_weapon, int new_weapon_ammo, int angle,
                                 const bool facing_left);

private:
    /**
     * @brief Updates the animations of the worm
     * @param up_an Up animation of the worm
     * @param down_an Down animation of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     */
    void update_animations(Animation& up_an, Animation& down_an, int angle, bool facing_left);
    /**
     * @brief Updates the animations of the worm when it is aiming
     * @param an Animation of the worm
     * @param up_an Up animation of the worm
     * @param down_an Down animation of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param aiming_angle Angle of the aiming of the worm
     * @param weapon Weapon of the worm
     */
    void update_aiming_animations(AnimationScroll& an, AnimationScroll& up_an,
                                  AnimationScroll& down_an, int angle, bool facing_left,
                                  int aiming_angle, TOOLS weapon);
    /**
     * @brief Resets the old animations of the worm that depends on the old angle and old
     * facing_left
     * @param an Animation of the worm
     * @param up_an Up animation of the worm
     * @param down_an Down animation of the worm
     */
    void reset_old_specific_an(Animation& an, Animation& up_an, Animation& down_an);
    /**
     * @brief Resets the old animations of the worm
     */
    void reset_old_an();
    /**
     * @brief Check if the worm state is an action state
     * @param state State of the worm
     * @return True if the worm state is an action state, false otherwise
     */
    bool is_action_state(int state);
    /**
     * @brief Check if the worm weapon is a grenade type
     * @param weapon Weapon of the worm
     * @return True if the worm weapon is a grenade type, false otherwise
     */
    bool is_weapon_grenade_type(TOOLS weapon);
    /**
     * @brief Renders the worm with the animation when it is still
     * @param weapon Weapon of the worm
     * @param weapon_ammo Ammo of the weapon of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param renderer Renderer of the match
     * @param dst Destination rectangle of the worm
     * @param flip Flip of the worm (SDL_FLIP_NONE or SDL_FLIP_HORIZONTAL)
     * @param left_offset Offset of the worm in the left side
     * @param right_offset Offset of the worm in the right side
     * @param above_offset Offset of the worm in the top side
     * @param bellow_offset Offset of the worm in the bottom side
     */
    void render_worm_still_with_weapon(TOOLS weapon, int weapon_ammo, const int angle,
                                       const bool facing_left, SDL2pp::Renderer& renderer,
                                       const SDL2pp::Rect dst, SDL_RendererFlip flip,
                                       int left_offset, int right_offset, int above_offset,
                                       int bellow_offset);
    /**
     * @brief Renders the worm with the animation that depends on the angle
     * @param an Animation of the worm
     * @param up_an Up animation of the worm
     * @param down_an Down animation of the worm
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param renderer Renderer of the match
     * @param dst Destination rectangle of the worm
     * @param flip Flip of the worm (SDL_FLIP_NONE or SDL_FLIP_HORIZONTAL)
     * @param left_offset Offset of the worm in the left side
     * @param right_offset Offset of the worm in the right side
     * @param above_offset Offset of the worm in the top side
     * @param bellow_offset Offset of the worm in the bottom side
     */
    void render_angle_dependent_an(Animation& an, Animation& up_an, Animation& down_an,
                                   const int angle, const bool facing_left,
                                   SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                   SDL_RendererFlip flip, int left_offset, int right_offset,
                                   int above_offset, int bellow_offset);
    /**
     * @brief Push back in the lingering animations list the changing weapons animation that depends
     * on the angle
     * @param middle_an Animation of the worm when is in flat surface
     * @param down_an Animation of the worm when is in a slope
     * @param up_an Animation of the worm when is in a slope
     * @param angle Angle of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     */
    void push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle,
                              const bool facing_left);
    void push_drop_weapon_an(int angle, const bool facing_left);
    void push_pick_up_weapon_an(TOOLS weapon, int weapon_ammo, int angle, const bool facing_left);

    std::list<std::reference_wrapper<Animation>> lingering_animations;
    /*WORM PREVIOUS INFO*/
    int old_state;
    int old_angle;
    TOOLS old_weapon;
    int old_weapon_ammo;
    bool old_facing_left;
    int old_aiming_angle;
    /*WORM MOVEMENTS*/
    Animation still_0_an;
    Animation still_0_up_an;
    Animation still_0_down_an;
    // Animation still_1_an;
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
