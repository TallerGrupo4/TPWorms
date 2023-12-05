#ifndef PROJECTILE_ANIMATIONS_H
#define PROJECTILE_ANIMATIONS_H

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

#include "Animation.h"
#include "AnimationAngle.h"
#include "client_constants.h"
#include "surfaces.h"

class ProjectileAnimations {
public:
    ProjectileAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(ProjectileStates state, ProjectileTypes type, int angle, SDL2pp::Renderer& renderer,
                const SDL2pp::Rect dst, const bool facing_left, int left_offset = 0,
                int right_offset = 0, int above_offset = 0, int bellow_offset = 0);
    void update_from_snapshot(ProjectileStates state, ProjectileTypes type);
    void update_from_iter(ProjectileStates state, ProjectileTypes type, int angle);

private:
    void render_angle_dependent_an(Animation& up_an, Animation& down_an, const int angle,
                                   const bool facing_left, SDL2pp::Renderer& renderer,
                                   const SDL2pp::Rect dst, SDL_RendererFlip flip, int left_offset,
                                   int right_offset, int above_offset, int bellow_offset);
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
