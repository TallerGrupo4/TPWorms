#include "camera.h"

Camera::Camera(uint turn_time, int map_width, int map_height) : map_width(map_width), map_height(map_height), hud(target, turn_time) {}

void Camera::update(Target target) {
    this->target = target;
    this->hud.update_target(target);
}

void Camera::update_turn_time_text(uint turn_time) {
    hud.update_turn_time_text(turn_time);
}

void Camera::render(SDL2pp::Renderer& renderer) {
    hud.render(renderer);
}

TargetType Camera::has_target() {
    return this->target.type_of_target;
}

int Camera::get_target_worm_id() {
    return this->target.worm_id;
}

int Camera::get_target_projectile_id() {
    return this->target.projectile_id;
}

int Camera::get_offset_x() {
    return this->target.x_offset;
}

int Camera::get_offset_y() {
    return this->target.y_offset;
}

void Camera::toogle_player_activated() {
    this->player_activated = this->player_activated ? false : true;
}

bool Camera::is_player_activated() {
    return this->player_activated;
}
