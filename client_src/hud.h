#ifndef HUD_H
#define HUD_H

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

class Hud {
private:
    Target target;
    SDL2pp::Surface turn_time_text;
    int my_army_id;
    int turn_army_id;
    bool marker_following_mouse;
    bool marker_set;
    int marker_x;
    int marker_y;
public:
    explicit Hud(Target target, uint turn_time);
    void update_target(Target target);
    void follow_mouse_with_marker(int mouse_x, int mouse_y);
    void set_marker_position(int x, int y);
    void take_out_marker();
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // HUD_H