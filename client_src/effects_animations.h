#ifndef EFFECTS_ANIMATIONS_H
#define EFFECTS_ANIMATIONS_H

#include <list>
#include <memory>
#include <utility>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

#include "Animation.h"
#include "client_constants.h"
#include "pos_explosion_animation.h"
#include "surfaces.h"

// Class that holds all the effects animations of the match
class EffectsAnimations {
public:
    /**
     * @brief Construct a new Effects Animations object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     */
    EffectsAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    /**
     * @brief Updates the effects animations from the ticks of the match
     */
    void update_from_iter();
    /**
     * @brief Renders the effects animations
     * @param renderer Renderer of the match
     * @param camara_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render(SDL2pp::Renderer& renderer, int camara_offset_x, int camera_offset_y);
    /**
     * @brief Sets the worm hit animation
     * @param renderer Renderer of the match
     * @param x X coordinate of the animation
     * @param y Y coordinate of the animation
     */
    void set_worm_hit_an(SDL2pp::Renderer& renderer, int x, int y);
    /**
     * @brief Sets the baseball bat hit animation
     * @param renderer Renderer of the match
     * @param x X coordinate of the animation
     * @param y Y coordinate of the animation
     */
    void set_baseball_bat_hit(SDL2pp::Renderer& renderer, int x, int y);
    /**
     * @brief Sets the big explosion animation
     * @param renderer Renderer of the match
     * @param x X coordinate of the animation
     * @param y Y coordinate of the animation
     * @param explosion_size Size of the explosion
     */
    void set_big_explosion_an(SDL2pp::Renderer& renderer, int x, int y, int explosion_size = 0);
    /**
     * @brief Sets the small explosion animation
     * @param renderer Renderer of the match
     * @param x X coordinate of the animation
     * @param y Y coordinate of the animation
     * @param explosion_size Size of the explosion
     */
    void set_small_explosion_an(SDL2pp::Renderer& renderer, int x, int y, int explosion_size = 0);
    /**
     * @brief Sets the missile exhaust animation
     * @param renderer Renderer of the match
     * @param x X coordinate of the animation
     * @param y Y coordinate of the animation
     */
    void set_missile_exhaust_an(SDL2pp::Renderer& renderer, int x, int y);

private:
    void renderAnimation(Animation& animation, SDL2pp::Renderer& renderer, int size, int x, int y,
                         SDL_RendererFlip flip, int camera_offset_x, int camera_offset_y);

    std::list<std::unique_ptr<PosExplosionAndAnimation>> lingering_animations;
    /*NEED OF ITER*/
    SDL2pp::Surface& small_explosion_circle_surface;
    SDL2pp::Surface& big_explosion_circle_surface;
    SDL2pp::Surface& small_explosion_rings_surface;
    SDL2pp::Surface& big_explosion_rings_surface;
    SDL2pp::Surface& missile_exhaust_surface;
    SDL2pp::Surface& baseball_bat_hit_surface;
    SDL2pp::Surface& worm_hit_surface;
};

#endif  // EFFECTS_ANIMATIONS_H
