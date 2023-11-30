#include "hud.h"

Hud::Hud(Target target, uint turn_time) : target(target),
     turn_time_text(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("Turn Time: " + std::to_string(turn_time)), {255, 0, 0})),
     my_army_id(-1),
     turn_army_id(-1),
     marker_following_mouse(false),
     marker_set(false),
     marker_x(0),
     marker_y(0) {}

void Hud::render(SDL2pp::Renderer& renderer) {
    switch (this->target.type_of_target) {
    case WormType:
    case PlayerType:
    case ProjectileType:
    case NoneType:
        SDL2pp::Texture turn_time_text_texture(renderer, this->turn_time_text);
        renderer.Copy(turn_time_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, this->turn_time_text.GetWidth(), this->turn_time_text.GetHeight()));
        break;
    }
}

void Hud::update_target(Target target) {
    this->target = target;
}

void Hud::follow_mouse_with_marker(int mouse_x, int mouse_y) {
    this->marker_following_mouse = true;
    this->marker_x = mouse_x;
    this->marker_y = mouse_y;
}

void Hud::set_marker_position(int x, int y) {
    this->marker_following_mouse = false;
    this->marker_set = true;
    this->marker_x = x;
    this->marker_y = y;
}

void Hud::take_out_marker() {
    this->marker_following_mouse = false;
    this->marker_set = false;
    this->marker_x = 0;
}

void Hud::update_turn_time_text(uint turn_time) {
    std::string turn_time_text_str = "Turn Time: " + std::to_string(turn_time);
    this->turn_time_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_time_text_str, {255, 0, 0});
}