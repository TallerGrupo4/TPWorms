#include "hud.h"

Hud::Hud() : target(),
            turn_time_text(nullptr),
            marker_an(nullptr),
            my_army_id(-1),
            turn_army_id(-1),
            marker_following_mouse(false),
            marker_set(false),
            marker_x(0),
            marker_y(0) {}

Hud::Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time, char my_army_id) : 
     target(target),
     turn_time_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("Turn Time: " + std::to_string(turn_time)), {255, 0, 0}))),
     marker_an(nullptr),
     my_army_id(my_army_id),
     turn_army_id(-1),
     marker_following_mouse(false),
     marker_set(false),
     marker_x(0),
     marker_y(0) {

    switch (my_army_id) {
    case 0:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_blue, SECS_FOR_MARKER_SPRITES);
        break;
    case 1:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_red, SECS_FOR_MARKER_SPRITES);
        break;
    case 2:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_yellow, SECS_FOR_MARKER_SPRITES);
        break;
    case 3:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_green, SECS_FOR_MARKER_SPRITES);
        break;
    default:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_purple, SECS_FOR_MARKER_SPRITES);
        break;
    }
}

void Hud::render(SDL2pp::Renderer& renderer) {

    if (marker_following_mouse) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        marker_an->render(renderer, SDL2pp::Rect(marker_x/* - this->target.x_offset*/ - marker_an->get_frame_size()/2, marker_y/* - this->target.y_offset*/ - marker_an->get_frame_size()/2, marker_an->get_frame_size(), marker_an->get_frame_size()), flip);
    } else if (marker_set) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        std::cout << "marker_x: " << marker_x << std::endl;
        std::cout << "marker_y: " << marker_y << std::endl;
        // marker_an->render(renderer, SDL2pp::Rect(marker_x/* - this->target.x_offset*/ - marker_an->get_frame_size()/2, marker_y/* - this->target.y_offset*/ - marker_an->get_frame_size()/2, marker_an->get_frame_size(), marker_an->get_frame_size()), flip);
        marker_an->render(renderer, SDL2pp::Rect(marker_x - this->target.x_offset - marker_an->get_frame_size()/2, marker_y - this->target.y_offset - marker_an->get_frame_size()/2, marker_an->get_frame_size(), marker_an->get_frame_size()), flip);
    }
    
    // switch (this->target.type_of_target) {
    // case WormType:
    // case PlayerType:
    // case ProjectileType:
    // case NoneType:
    //     SDL2pp::Texture turn_time_text_texture(renderer, this->turn_time_text);
    //     renderer.Copy(turn_time_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, this->turn_time_text.GetWidth(), this->turn_time_text.GetHeight()));
    //     break;
    // }
    SDL2pp::Texture turn_time_text_texture(renderer, *this->turn_time_text);
    renderer.Copy(turn_time_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, (*this->turn_time_text).GetWidth(), (*this->turn_time_text).GetHeight()));
        
}

void Hud::update_target(Target target) {
    this->target = target;
}

void Hud::update_from_iter() {
    if (marker_following_mouse or marker_set) {
    this->marker_an->update_once();
    }
    
}

void Hud::update_marker(int x, int y) {
    if (marker_following_mouse) {
        this->marker_x = x;
        this->marker_y = y;
    }
}

void Hud::follow_mouse_with_marker(int mouse_x, int mouse_y) {
    this->marker_an->reset();
    this->marker_set = false;
    this->marker_following_mouse = true;
    this->marker_x = mouse_x;
    this->marker_y = mouse_y;
}

void Hud::set_marker_position(int x, int y) {
    if (not marker_set) {
        this->marker_an->reset();
        this->marker_following_mouse = false;
        this->marker_set = true;
        this->marker_x = x + this->target.x_offset;
        this->marker_y = y + this->target.y_offset;
    } else {
        this->marker_an->reset();
        this->marker_x = x + this->target.x_offset;
        this->marker_y = y + this->target.y_offset;
    }
}

void Hud::take_out_marker() {
    this->marker_following_mouse = false;
    this->marker_set = false;
    this->marker_x = 0;
    this->marker_y = 0;
}

int Hud::get_marker_x(){
    return this->marker_x;
}

int Hud::get_marker_y(){
    return this->marker_y;
}

void Hud::update_turn_time_text(uint turn_time) {
    std::string turn_time_text_str = "Turn Time: " + std::to_string(turn_time);
    *this->turn_time_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_time_text_str, {255, 0, 0});
}

bool Hud::is_marker_set() {
    return this->marker_set;
}

bool Hud::is_marker_active() {
    return (this->marker_set or this->marker_following_mouse);
}
