#ifndef WORM_ANIMATIONS_H
#define WORM_ANIMATIONS_H

#include <memory>
#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"

class WormAnimations {
public:
    WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(int state, int angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       const bool facing_left,
                       int left_offset = 0,
                       int right_offset = 0,
                       int above_offset = 0,
                       int bellow_offset = 0);
    void update_from_snapshot(int state, int angle, bool facing_left);
    void update_from_iter(int state, int angle, bool facing_left);
    void update_changing_weapons(TOOLS actual_weapon, TOOLS new_weapon, int angle, const bool facing_left);
private:
    bool is_action_state(int state);
    void render_angle_dependent_an(Animation& up_an, Animation& down_an,
                                    const int angle, const bool facing_left,
                                    SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                    SDL_RendererFlip flip,
                                    int left_offset,
                                    int right_offset,
                                    int above_offset,
                                    int bellow_offset);
    void push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left);
    void push_drop_weapon_an(TOOLS weapon, int angle, const bool facing_left);
    void push_pick_up_weapon_an(TOOLS weapon, int angle, const bool facing_left);

    std::list<std::reference_wrapper<Animation>> lingering_animations;
    Animation still_0_an;
    Animation still_0_up_an;
    Animation still_0_down_an;
    Animation still_1_an;
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
    /*WORM CHANGING WEAPONS*/
    Animation get_baz_an;
    Animation get_baz_up_an;
    Animation get_baz_down_an;
    Animation drop_baz_an;
    Animation drop_baz_up_an;
    Animation drop_baz_down_an;
    /*WORM AIMING WEAPONS*/
    Animation aim_baz_an;
    Animation aim_baz_up_an;
    Animation aim_baz_down_an;
};

#endif  // WORM_ANIMATIONS_H