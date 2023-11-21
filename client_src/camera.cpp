#include "camera.h"

Camera::Camera(int map_width, int map_height) : map_width(map_width), map_height(map_height) {}

void Camera::update(Target target) {
    this->target = target;
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
