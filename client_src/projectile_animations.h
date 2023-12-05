#ifndef PROJECTILE_ANIMATIONS_H
#define PROJECTILE_ANIMATIONS_H

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

#include "Animation.h"
#include "AnimationAngle.h"
#include "client_constants.h"
#include "surfaces.h"

// Class that represents the animations of a projectile
class ProjectileAnimations {
public:
    /**
     * @brief Construct a new Projectile Animations object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     */
    ProjectileAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    /**
     * @brief Renders the projectile animation
     * @param state State of the projectile
     * @param type Type of the projectile
     * @param angle Angle of the projectile
     * @param renderer Renderer of the match
     * @param dst Destination rectangle of the projectile
     * @param facing_left True if the projectile is facing left, false otherwise
     * @param left_offset Offset of the left side of the projectile
     * @param right_offset Offset of the right side of the projectile
     * @param above_offset Offset of the top side of the projectile
     * @param bellow_offset Offset of the bottom side of the projectile
     */
    void render(ProjectileStates state, ProjectileTypes type, int angle, SDL2pp::Renderer& renderer,
                const SDL2pp::Rect dst, const bool facing_left, int left_offset = 0,
                int right_offset = 0, int above_offset = 0, int bellow_offset = 0);
    /**
     * @brief Updates the projectile from the snapshot received from the server
     * @param state State of the projectile
     * @param type Type of the projectile
     */
    void update_from_snapshot(ProjectileStates state, ProjectileTypes type);
    /**
     * @brief Updates the projectile from the ticks of the match
     * @param state State of the projectile
     * @param type Type of the projectile
     * @param angle Angle of the projectile
     */
    void update_from_iter(ProjectileStates state, ProjectileTypes type, int angle);

private:
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
