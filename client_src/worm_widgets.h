#ifndef WORM_WIDGETS_H
#define WORM_WIDGETS_H

#include <cmath>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "client_constants.h"
#include "colordependentwidgets.h"

// Class that represents the widgets of a worm
class WormWidgets {
private:
    SDL_Color player_color;
    Animation crosshair_an;
    int crosshair_angle;
    int crosshair_x;
    int crosshair_y;
    SDL2pp::Texture army_text;
    SDL2pp::Texture worm_text;
    SDL2pp::Surface health_text;

    /**
     * @brief Renders the background of the texts
     * @param renderer Renderer of the match
     * @param x X coordinate of the text
     * @param y Y coordinate of the text
     * @param text Texture of the text
     */
    void renderTextBackground(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text);
    /**
     * @brief Renders the text
     * @param renderer Renderer of the match
     * @param x X coordinate of the text
     * @param y Y coordinate of the text
     * @param text Texture of the text
     */
    void renderText(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text);
    /**
     * @brief Handles the aiming state of the worm and renders the crosshair
     * @param renderer Renderer of the match
     * @param facing_left True if the worm is facing left, false otherwise
     * @param worm_center_x X coordinate of the center of the worm
     * @param worm_center_y Y coordinate of the center of the worm
     */
    void handleAimingState(SDL2pp::Renderer& renderer, bool facing_left, int worm_center_x,
                           int worm_center_y);

public:
    /**
     * @brief Constructs a new Worm Widgets object
     * @param renderer Renderer of the match
     * @param army_id Id of the army of the worm
     * @param widgets Widgets of the army
     * @param worm_id Id of the worm
     * @param health_points Health points of the worm
     * @param max_health Maximum health points of the worm
     */
    explicit WormWidgets(SDL2pp::Renderer& renderer, char army_id,
                         ArmyColorDependentWidgets widgets, char worm_id, int health_points,
                         int max_health);
    /**
     * @brief Updates the health text
     * @param health_points Health points of the worm
     * @param max_health Maximum health points of the worm
     */
    void update_health(int health_points, int max_health);
    /**
     * @brief Updates the crosshair angle
     * @param angle Angle of the crosshair
     */
    void update_crosshair(int angle);
    /**
     * @brief Updates the crosshair animation
     */
    void update_crosshair_from_iter();
    /**
     * @brief Renders the widgets of the worm
     * @param renderer Renderer of the match
     * @param worm_state State of the worm
     * @param facing_left True if the worm is facing left, false otherwise
     * @param worm_center_x X coordinate of the center of the worm
     * @param worm_center_y Y coordinate of the center of the worm
     * @param worm_top_y Y coordinate of the top of the worm
     * @param worm_botom_y Y coordinate of the bottom of the worm
     */
    void render(SDL2pp::Renderer& renderer, int worm_state, bool facing_left, int worm_center_x,
                int worm_center_y, int worm_top_y, int worm_botom_y);
    int get_crosshair_x();
    int get_crosshair_y();
};

#endif  // WORM_WIDGETS_H
