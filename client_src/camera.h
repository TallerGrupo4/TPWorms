#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"
#include "hud.h"

class Camera {
private:
    Target target;
    int map_width;
    int map_height;
    Hud hud;
    bool player_activated = false;


public:
    explicit Camera(uint turn_time = 0, int map_width = 0, int map_height = 0);
    void update(Target target);
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
    TargetType has_target();
    int get_target_worm_id();
    int get_target_projectile_id();
    int get_offset_x();
    int get_offset_y();
    void toogle_player_activated();
    bool is_player_activated();
};

#endif  // CAMERA_H