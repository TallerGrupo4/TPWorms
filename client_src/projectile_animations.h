// #ifndef PROJECTILE_ANIMATIONS_H
// #define PROJECTILE_ANIMATIONS_H

// #include <memory>
// #include <list>

// #include <SDL2pp/SDL2pp.hh>

// #include "../common_src/constants.h"
// #include "constantes_cliente.h"
// #include "surfaces.h"
// #include "Animation.h"
// #include "AnimationScroll.h"

// class ProjectileAnimations {
// public:
//     ProjectileAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
//     void render(ProjectileStates state, int angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
//                        const bool facing_left,
//                        int left_offset = 0,
//                        int right_offset = 0,
//                        int above_offset = 0,
//                        int bellow_offset = 0);
//     void update_from_snapshot(ProjectileStates state, int angle, bool facing_left);
//     void update_from_iter(ProjectileStates state, int angle, bool facing_left);
// private:
//     bool is_action_state(ProjectileStates state);
//     // void check_aiming_angle(AnimationScroll& an, int new_aiming_angle, int old_aiming_angle);
//     void render_angle_dependent_an(Animation& up_an, Animation& down_an,
//                                     const int angle, const bool facing_left,
//                                     SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
//                                     SDL_RendererFlip flip,
//                                     int left_offset,
//                                     int right_offset,
//                                     int above_offset,
//                                     int bellow_offset);
//     // void push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left);
//     // void push_drop_weapon_an(TOOLS weapon, int angle, const bool facing_left);
//     // void push_pick_up_weapon_an(TOOLS weapon, int angle, const bool facing_left);

//     std::list<std::reference_wrapper<Animation>> lingering_animations;
//     Animation still_0_an;
//     AnimationScroll aim_baz_down_an;
// };

// #endif  // PROJECTILE_ANIMATIONS_H