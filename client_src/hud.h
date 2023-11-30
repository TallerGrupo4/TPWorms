#ifndef HUD_H
#define HUD_H

#include <memory>
#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"

class Hud {
private:
    Target target;
    std::shared_ptr<SDL2pp::Surface> turn_time_text;
    std::unique_ptr<Animation> marker_an;
    int my_army_id;
    int turn_army_id;
    bool marker_following_mouse;
    bool marker_set;
    int marker_x;
    int marker_y;
public:
    explicit Hud();
    explicit Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time, char my_army_id);
    void update_target(Target target);
    void update_from_iter();
    void follow_mouse_with_marker(int mouse_x, int mouse_y);
    void set_marker_position(int x, int y);
    void take_out_marker();
    int get_marker_x();
    int get_marker_y();
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // HUD_H