#ifndef PROJECTILE_ANIMATIONS_H
#define PROJECTILE_ANIMATIONS_H

#include <memory>
#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"
#include "AnimationAngle.h"

class ProjectileAnimations {
public:
    ProjectileAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(ProjectileStates state, ProjectileTypes type, int angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       const bool facing_left,
                       int left_offset = 0,
                       int right_offset = 0,
                       int above_offset = 0,
                       int bellow_offset = 0);
    void update_from_snapshot(ProjectileStates state, ProjectileTypes type);
    void update_from_iter(ProjectileStates state, ProjectileTypes type, int angle);
private:
    //bool is_action_state(ProjectileStates state);
    // void check_aiming_angle(AnimationScroll& an, int new_aiming_angle, int old_aiming_angle);
    void render_angle_dependent_an(Animation& up_an, Animation& down_an,
                                    const int angle, const bool facing_left,
                                    SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                    SDL_RendererFlip flip,
                                    int left_offset,
                                    int right_offset,
                                    int above_offset,
                                    int bellow_offset);
    // void push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left);
    // void push_drop_weapon_an(TOOLS weapon, int angle, const bool facing_left);
    // void push_pick_up_weapon_an(TOOLS weapon, int angle, const bool facing_left);

    //std::list<std::reference_wrapper<Animation>> lingering_animations;
    /*NEED OF ITER*/
    Animation ban_an;
    Animation gr_an;
    Animation cls_an;
    Animation cls_fragment_an;
    Animation dyn_an;
    Animation holy_grenade_an;
    /*NO NEED OF ITER*/
    AnimationAngle bazooka_missile_an;
    AnimationAngle mortar_round_an;
    AnimationAngle air_missile_an;
};

#endif  // PROJECTILE_ANIMATIONS_H