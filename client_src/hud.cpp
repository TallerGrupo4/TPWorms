#include "hud.h"

Hud::Hud() : target(),
            marker_an(nullptr),
            turn_time_text(nullptr),
            timer_text(nullptr),
            charging_text(nullptr),
            turn_army_text(nullptr),
            end_game_text(nullptr),
            my_army_id(-1),
            my_army_color(WHITE),
            marker_following_mouse(false),
            marker_set(false),
            is_end_game(false),
            marker_x(0),
            marker_y(0) {}

Hud::Hud(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces, Target target, uint turn_time, char my_army_id) : 
     target(target),
     marker_an(nullptr),
     turn_time_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("Turn Time: " + std::to_string(turn_time)), WHITE))),
     timer_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("Grenade Timer: "), WHITE))),
     charging_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("Weapon Charge: "), WHITE))),
     turn_army_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(std::string("PLACEHOLDER TEXT TURN ARMY"), WHITE))),
     end_game_text(std::make_shared<SDL2pp::Surface>(SDL2pp::Font(WORMS_FONT_PATH, 64).RenderText_Blended(std::string("PLACEHOLDER TEXT END GAME"), WHITE))),
     my_army_id(my_army_id),
     my_army_color(WHITE),
     marker_following_mouse(false),
     marker_set(false),
     is_end_game(false),
     marker_x(0),
     marker_y(0) {

    switch (my_army_id) {
    case 0:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_blue, SECS_FOR_MARKER_SPRITES);
        my_army_color = BLUE;
        break;
    case 1:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_red, SECS_FOR_MARKER_SPRITES);
        my_army_color = RED;
        break;
    case 2:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_yellow, SECS_FOR_MARKER_SPRITES);
        my_army_color = YELLOW;
        break;
    case 3:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_green, SECS_FOR_MARKER_SPRITES);
        my_army_color = GREEN;
        break;
    default:
        marker_an = std::make_unique<Animation>(renderer, surfaces.marker_purple, SECS_FOR_MARKER_SPRITES);
        my_army_color = ORANGE;
        break;
    }
}

void Hud::render(SDL2pp::Renderer& renderer) {
    if (is_end_game) {
        SDL2pp::Texture end_game_text_texture(renderer, *this->end_game_text);
        renderer.Copy(end_game_text_texture, SDL2pp::NullOpt, SDL2pp::Rect((renderer.GetLogicalWidth()/2)-((*this->end_game_text).GetWidth()/2), (renderer.GetLogicalHeight()/2)-((*this->end_game_text).GetHeight()/2), (*this->end_game_text).GetWidth(), (*this->end_game_text).GetHeight()));
    } else {
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
        SDL2pp::Texture turn_time_text_texture(renderer, *this->turn_time_text);
        renderer.Copy(turn_time_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, 0, (*this->turn_time_text).GetWidth(), (*this->turn_time_text).GetHeight()));  
        SDL2pp::Texture turn_army_text_texture(renderer, *this->turn_army_text);
        renderer.Copy(turn_army_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, (*this->turn_time_text).GetHeight() + 10, (*this->turn_army_text).GetWidth(), (*this->turn_army_text).GetHeight()));  
        SDL2pp::Texture timer_text_texture(renderer, *this->timer_text);
        renderer.Copy(timer_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, renderer.GetLogicalHeight()-10 - (*this->timer_text).GetHeight(), (*this->timer_text).GetWidth(), (*this->timer_text).GetHeight())); 
        SDL2pp::Texture charging_text_texture(renderer, *this->charging_text);
        renderer.Copy(charging_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(0, renderer.GetLogicalHeight() - (*this->timer_text).GetHeight() - 20 - (*this->charging_text).GetHeight(), (*this->charging_text).GetWidth(), (*this->charging_text).GetHeight()));  
    }
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

void Hud::set_army_turn(char worm_turn_army_id) {
    if(this->my_army_id == worm_turn_army_id) {
        std::string turn_army_text_str = "My Turn";
        *this->turn_army_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_army_text_str, my_army_color);
    } else {
        SDL_Color turn_color;
        switch (worm_turn_army_id) {
        case 0:
            turn_color = BLUE;
            break;
        case 1:
            turn_color = RED;
            break;
        case 2:
            turn_color = YELLOW;
            break;
        case 3:
            turn_color = GREEN;
            break;
        default:
            turn_color = ORANGE;
            break;
        }
        std::string turn_army_text_str = "Player " + std::to_string(worm_turn_army_id+1) + " Turn";
        *this->turn_army_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_army_text_str, turn_color);
    }
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

void Hud::set_charging_value(int charge) {
    std::string charging_text_str = "Weapon Charge: " + std::to_string(charge);
    *this->charging_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(charging_text_str, WHITE);
}

void Hud::clear_charging_value() {
    std::string charging_text_str = "Weapon Charge: ";
    *this->charging_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(charging_text_str, WHITE);
}

void Hud::set_timer(int timer) {
    std::string timer_text_str = "Grenade Timer: " + std::to_string(timer);
    *this->timer_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(timer_text_str, WHITE);
}

void Hud::clear_timer_value() {
    std::string timer_text_str = "Grenade Timer: ";
    *this->timer_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(timer_text_str, WHITE);
}

void Hud::set_end_game(char winner_team_id) {
    this->is_end_game = true;
    if(this->my_army_id == winner_team_id) {
        std::string end_game_text_str = "Congratulations! You Won!";
        *this->end_game_text = SDL2pp::Font(WORMS_FONT_PATH, 32).RenderText_Blended(end_game_text_str, my_army_color);
    } else {
        SDL_Color winner_color;
        switch (winner_team_id) {
        case 0:
            winner_color = BLUE;
            break;
        case 1:
            winner_color = RED;
            break;
        case 2:
            winner_color = YELLOW;
            break;
        case 3:
            winner_color = GREEN;
            break;
        default:
            winner_color = ORANGE;
            break;
        }
        std::string end_game_text_str = "Bad Luck! Player " + std::to_string(winner_team_id+1) + " Won!";
        *this->end_game_text = SDL2pp::Font(WORMS_FONT_PATH, 32).RenderText_Blended(end_game_text_str, winner_color);
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
    *this->turn_time_text = SDL2pp::Font(WORMS_FONT_PATH, 16).RenderText_Blended(turn_time_text_str, WHITE);
}

bool Hud::is_marker_set() {
    return this->marker_set;
}

bool Hud::is_marker_active() {
    return (this->marker_set or this->marker_following_mouse);
}
