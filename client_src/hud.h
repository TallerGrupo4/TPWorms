#ifndef HUD_H
#define HUD_H

#include <memory>
#include <map>
#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"

class Hud {
private:
    Target target;
    std::unique_ptr<Animation> marker_an;
    /*TEXTS*/
    std::shared_ptr<SDL2pp::Surface> turn_time_text;
    std::shared_ptr<SDL2pp::Surface> ammo_text;
    std::shared_ptr<SDL2pp::Surface> timer_text;
    std::shared_ptr<SDL2pp::Surface> charging_text;
    std::shared_ptr<SDL2pp::Surface> turn_army_text;
    std::shared_ptr<SDL2pp::Surface> end_game_text;
    std::map<char,std::shared_ptr<SDL2pp::Surface>> armies_health_texts;
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
    explicit Hud();
    explicit Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time, char my_army_id);
    void update_target(Target target);
    void update_turn_weapon(TOOLS turn_worm_weapon);
    void update_turn_weapon_ammo(int turn_worm_weapon_ammo);
    void update_armies_health(std::map<char, int>& armies_health);
    void update_from_iter();
    void update_marker(int x, int y);
    void follow_mouse_with_marker(int mouse_x, int mouse_y);
    void set_army_turn(char worm_turn_army_id);
    void set_marker_position(int x, int y);
    void set_charging_value(int charge);
    void clear_charging_value();
    void set_timer(int timer);
    void clear_timer_value();
    void set_end_game(char winner_team_id);
    void take_out_marker();
    int get_marker_x();
    int get_marker_y();
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
    bool is_marker_set();
    bool is_marker_active();
};

#endif  // HUD_H