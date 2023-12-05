#include "camera.h"

Camera::Camera() {}

Camera::Camera(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, uint turn_time, char my_army_id,
               int map_width, int map_height):
        map_width(map_width),
        map_height(map_height),
        hud(renderer, surfaces, target, turn_time, my_army_id),
        player_activated(false) {}

void Camera::update(Target target) {
    this->target = target;
    this->hud.update_target(target);
}

void Camera::update_hud() { this->hud.update_marker_an(); }

void Camera::update_marker(int x, int y) { this->hud.update_marker(x, y); }

void Camera::update_turn_weapon(TOOLS turn_worm_weapon) {
    this->hud.update_turn_weapon(turn_worm_weapon);
}

void Camera::update_turn_weapon_ammo(int turn_worm_weapon_ammo) {
    this->hud.update_turn_weapon_ammo(turn_worm_weapon_ammo);
}

void Camera::update_wind_velocity(int wind_velocity) {
    this->hud.update_wind_velocity(wind_velocity);
}

void Camera::update_armies_health(const std::map<char, int>& armies_health) {
    this->hud.update_armies_health(armies_health);
}

void Camera::follow_mouse_with_marker(int mouse_x, int mouse_y) {
    this->hud.follow_mouse_with_marker(mouse_x, mouse_y);
}

void Camera::set_army_turn(char worm_turn_army_id) { this->hud.set_army_turn(worm_turn_army_id); }

void Camera::set_marker_position(int x, int y) { this->hud.set_marker_position(x, y); }

void Camera::set_charging_value(int charge) { this->hud.set_charging_value(charge); }

void Camera::clear_charging_value() { this->hud.clear_charging_value(); }

void Camera::set_timer(int timer) { this->hud.set_timer(timer); }

void Camera::clear_timer_value() { this->hud.clear_timer_value(); }

void Camera::set_end_game(char winner_team_id) { this->hud.set_end_game(winner_team_id); }

void Camera::take_out_marker() { this->hud.take_out_marker(); }

void Camera::update_turn_time_text(uint turn_time) { hud.update_turn_time_text(turn_time); }

void Camera::render(SDL2pp::Renderer& renderer) { hud.render(renderer); }

TargetType Camera::has_target() { return this->target.type_of_target; }

int Camera::get_target_worm_id() { return this->target.worm_id; }

int Camera::get_target_proj_id() { return this->target.projectile_id; }

int Camera::get_marker_x() { return this->hud.get_marker_x(); }

int Camera::get_marker_y() { return this->hud.get_marker_y(); }

int Camera::get_offset_x() { return this->target.x_offset; }

int Camera::get_offset_y() { return this->target.y_offset; }

void Camera::toogle_player_activated(SDL2pp::Window& window, int pos_x_to_warp_mouse,
                                     int pos_y_to_warp_mouse) {
    if (player_activated) {
        SDL_WarpMouseInWindow(window.Get(), pos_x_to_warp_mouse, pos_y_to_warp_mouse);
        player_activated = false;
    } else {
        player_activated = true;
    }
}

bool Camera::is_player_activated() { return this->player_activated; }

bool Camera::is_marker_set() { return this->hud.is_marker_set(); }

bool Camera::is_marker_active() { return this->hud.is_marker_active(); }
