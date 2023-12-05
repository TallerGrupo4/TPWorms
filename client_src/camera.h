#ifndef CAMERA_H
#define CAMERA_H

#include <map>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"
#include "hud.h"
#include "surfaces.h"

// Class that represents the camera of the match
class Camera {
private:
    Target target;
    int map_width;
    int map_height;
    Hud hud;
    bool player_activated;


public:
    Camera();
    /**
     * @brief Construct a new Camera object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     * @param turn_time Time of the turn
     * @param my_army_id Id of the army of the player
     * @param map_width Width of the map
     * @param map_height Height of the map
     */
    explicit Camera(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, uint turn_time,
                    char my_army_id, int map_width, int map_height);
    /**
     * @brief Updates the camera based upon the target given
     * @param target Actual target of the match
     */
    void update(Target target);
    // Updates the HUD
    void update_hud();
    /**
     * @brief Updates the marker position from guided weapons
     * @param x X coordinate of the marker
     * @param y Y coordinate of the marker
     */
    void update_marker(int x, int y);
    /**
     * @brief Updates the marker position from the mouse
     * @param mouse_x X coordinate of the mouse
     * @param mouse_y Y coordinate of the mouse
     */
    void follow_mouse_with_marker(int mouse_x, int mouse_y);
    /**
     * @brief Updates the weapon selected from the turn worm
     * @param turn_worm_weapon Weapon selected from the turn worm
     */
    void update_turn_weapon(TOOLS turn_worm_weapon);
    /**
     * @brief Updates the ammo of the weapon selected from the turn worm
     * @param turn_worm_weapon_ammo Ammo of the weapon selected from the turn worm
     */
    void update_turn_weapon_ammo(int turn_worm_weapon_ammo);
    /**
     * @brief Updates the wind velocity text
     * @param wind_velocity Wind velocity
     */
    void update_wind_velocity(int wind_velocity);
    /**
     * @brief Updates the health of the armies
     * @param armies_health Map of the armies health (army_id, health)
     */
    void update_armies_health(const std::map<char, int>& armies_health);
    /**
     * @brief Set the army turn text
     * @param worm_turn_army_id Id of the army of the turn worm
     */
    void set_army_turn(char worm_turn_army_id);
    /**
     * @brief Set the marker position
     * @param x X coordinate of the marker
     * @param y Y coordinate of the marker
     */
    void set_marker_position(int x, int y);
    /**
     * @brief Set the charging value
     * @param charge Value of the charge
     */
    void set_charging_value(int charge);
    /**
     * @brief Set the timer value
     * @param timer Value of the timer
     */
    void set_timer(int timer);
    /**
     * @brief Clear the charging value
     */
    void clear_charging_value();
    /**
     * @brief Clear the timer value
     */
    void clear_timer_value();
    /**
     * @brief Set the end game text
     * @param winner_team_id Id of the army that won the match
     */
    void set_end_game(char winner_team_id);
    /**
     * @brief Takes out the marker
     */
    void take_out_marker();
    /**
     * @brief Updates the turn time text
     * @param turn_time Time of the turn
     */
    void update_turn_time_text(uint turn_time);
    /**
     * @brief Renders the camera
     * @param renderer Renderer of the match
     */
    void render(SDL2pp::Renderer& renderer);
    TargetType has_target();
    int get_target_worm_id();
    int get_target_proj_id();
    int get_marker_x();
    int get_marker_y();
    int get_offset_x();
    int get_offset_y();
    /**
     * @brief Warp the mouse to the center of the window if the player is in lookout mode
     * @param window Window of the match
     * @param pos_x_to_warp_mouse X coordinate of the position to warp the mouse
     * @param pos_y_to_warp_mouse Y coordinate of the position to warp the mouse
     */
    void toogle_player_activated(SDL2pp::Window& window, int pos_x_to_warp_mouse,
                                 int pos_y_to_warp_mouse);
    bool is_player_activated();
    bool is_marker_set();
    bool is_marker_active();
};

#endif  // CAMERA_H
