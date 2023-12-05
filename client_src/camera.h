#ifndef CAMERA_H
#define CAMERA_H

#include <map>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"
#include "hud.h"
#include "surfaces.h"

class Camera {
private:
    Target target;
    int map_width;
    int map_height;
    Hud hud;
    bool player_activated;


public:
    Camera();
    explicit Camera(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, uint turn_time,
                    char my_army_id, int map_width, int map_height);
    void update(Target target);
    void update_hud();
    void update_marker(int x, int y);
    void update_turn_weapon(TOOLS turn_worm_weapon);
    void update_turn_weapon_ammo(int turn_worm_weapon_ammo);
    void update_wind_velocity(int wind_velocity);
    void update_armies_health(const std::map<char, int>& armies_health);
    void follow_mouse_with_marker(int mouse_x, int mouse_y);
    void set_army_turn(char worm_turn_army_id);
    void set_marker_position(int x, int y);
    void set_charging_value(int charge);
    void clear_charging_value();
    void set_timer(int timer);
    void clear_timer_value();
    void set_end_game(char winner_team_id);
    void take_out_marker();
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
    TargetType has_target();
    int get_target_worm_id();
    int get_target_proj_id();
    int get_marker_x();
    int get_marker_y();
    int get_offset_x();
    int get_offset_y();
    void toogle_player_activated(SDL2pp::Window& window, int pos_x_to_warp_mouse,
                                 int pos_y_to_warp_mouse);
    bool is_player_activated();
    bool is_marker_set();
    bool is_marker_active();
};

#endif  // CAMERA_H
