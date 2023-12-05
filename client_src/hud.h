#ifndef HUD_H
#define HUD_H

#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "client_constants.h"
#include "surfaces.h"

// Class that represents the HUD of the match
class Hud {
private:
    Target target;
    std::unique_ptr<Animation> marker_an;
    /*TEXTS*/
    std::shared_ptr<SDL2pp::Surface> wind_velocity_text;
    std::shared_ptr<SDL2pp::Surface> turn_time_text;
    std::shared_ptr<SDL2pp::Surface> ammo_text;
    std::shared_ptr<SDL2pp::Surface> timer_text;
    std::shared_ptr<SDL2pp::Surface> charging_text;
    std::shared_ptr<SDL2pp::Surface> turn_army_text;
    std::shared_ptr<SDL2pp::Surface> end_game_text;
    std::map<char, std::shared_ptr<SDL2pp::Surface>> armies_health_texts;
    /*WEAPON ICONS*/
    std::shared_ptr<SDL2pp::Texture> bazooka_icon_on;
    std::shared_ptr<SDL2pp::Texture> bazooka_icon_off;
    std::shared_ptr<SDL2pp::Texture> mortar_icon_on;
    std::shared_ptr<SDL2pp::Texture> mortar_icon_off;
    std::shared_ptr<SDL2pp::Texture> green_grenade_icon_on;
    std::shared_ptr<SDL2pp::Texture> green_grenade_icon_off;
    std::shared_ptr<SDL2pp::Texture> red_grenade_icon_on;
    std::shared_ptr<SDL2pp::Texture> red_grenade_icon_off;
    std::shared_ptr<SDL2pp::Texture> banana_icon_on;
    std::shared_ptr<SDL2pp::Texture> banana_icon_off;
    std::shared_ptr<SDL2pp::Texture> holy_icon_on;
    std::shared_ptr<SDL2pp::Texture> holy_icon_off;
    std::shared_ptr<SDL2pp::Texture> air_strike_icon_on;
    std::shared_ptr<SDL2pp::Texture> air_strike_icon_off;
    std::shared_ptr<SDL2pp::Texture> dynamite_icon_on;
    std::shared_ptr<SDL2pp::Texture> dynamite_icon_off;
    std::shared_ptr<SDL2pp::Texture> teleport_icon_on;
    std::shared_ptr<SDL2pp::Texture> teleport_icon_off;
    std::shared_ptr<SDL2pp::Texture> baseball_bat_icon_on;
    std::shared_ptr<SDL2pp::Texture> baseball_bat_icon_off;
    char my_army_id;
    SDL_Color my_army_color;
    TOOLS turn_worm_weapon;
    bool marker_following_mouse;
    bool marker_set;
    bool is_end_game;
    int marker_x;
    int marker_y;

    void render_weapon_icons(SDL2pp::Renderer& renderer);
    void render_armies_health(SDL2pp::Renderer& renderer, int army_health_pos_y);

public:
    Hud();
    /**
     * @brief Construct a new Hud object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     * @param target Target of the match
     * @param turn_time Time of the turn
     * @param my_army_id Id of the user army
     */
    explicit Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time,
                 char my_army_id);
    /**
     * @brief Updates the HUD based upon the target given
     * @param target Target of the match
     */
    void update_target(Target target);
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
     * @brief Updates the armies health texts
     * @param armies_health Map of the armies health (army_id, health)
     */
    void update_armies_health(const std::map<char, int>& armies_health);
    /**
     * @brief Updates Marker animation
     */
    void update_marker_an();
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
     * @brief Sets the marker position
     * @param x X coordinate of the marker
     * @param y Y coordinate of the marker
     */
    void set_marker_position(int x, int y);
    /**
     * @brief Sets the army turn text
     * @param worm_turn_army_id Id of the army of the worm that is playing
     */
    void set_army_turn(char worm_turn_army_id);
    /**
     * @brief Sets the charging value when firing a weapon
     * @param charge Value of the charge
     */
    void set_charging_value(int charge);
    /**
     * @brief Clears the charging texts
     */
    void clear_charging_value();
    /**
     * @brief Sets the timer value when using grenade types weapons
     * @param timer Value of the timer
     */
    void set_timer(int timer);
    /**
     * @brief Clears the timer texts
     */
    void clear_timer_value();
    /**
     * @brief Sets the end game text
     * @param winner_team_id Id of the winner team
     */
    void set_end_game(char winner_team_id);
    /**
     * @brief Take out the marker
     */
    void take_out_marker();
    int get_marker_x();
    int get_marker_y();
    /**
     * @brief Updates the turn time text
     * @param turn_time Time of the turn
     */
    void update_turn_time_text(uint turn_time);
    /**
     * @brief Renders the HUD
     * @param renderer Renderer of the match
     */
    void render(SDL2pp::Renderer& renderer);
    bool is_marker_set();
    bool is_marker_active();
};

#endif  // HUD_H
