#ifndef CAMERA_H
#define CAMERA_H

#include "constantes_cliente.h"

class Camera {
private:
    Target target;
    int map_width;
    int map_height;

public:
    explicit Camera(int map_width = 0, int map_height = 0);
    void update(Target target);
    TargetType has_target();
    int get_target_worm_id();
    int get_target_projectile_id();
    int get_offset_x();
    int get_offset_y();
};

#endif  // CAMERA_H