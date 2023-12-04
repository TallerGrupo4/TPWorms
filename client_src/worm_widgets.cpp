#include "worm_widgets.h"

WormWidgets::WormWidgets(SDL2pp::Renderer& renderer, char army_id, ArmyColorDependentWidgets widgets, char worm_id, int health_points, int max_health) :
    player_color(widgets.get_worm_color()),
    crosshair_an(renderer, widgets.get_crosshair(), SECS_FOR_CROSSHAIR_SPRITES),
    crosshair_angle(0),
    crosshair_x(0),
    crosshair_y(0),
    army_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Player " + std::to_string(army_id+1)), player_color)),
    worm_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Worm " + std::to_string(worm_id+1)), player_color)),
    health_text(SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string(std::to_string(health_points) + "/" + std::to_string(max_health)), player_color)) {}

void WormWidgets::update_health(int health_points, int max_health) {
    std::string health_text_str = std::to_string(health_points) + "/" + std::to_string(max_health);
    SDL2pp::Font worm_text_font(WORMS_FONT_PATH, WORM_FONT_SIZE);
    this->health_text = worm_text_font.RenderText_Blended(health_text_str, player_color);
}

void WormWidgets::update_crosshair(int angle) {
    this->crosshair_angle = angle;
}

void WormWidgets::update_crosshair_from_iter() {
    this->crosshair_an.update_once();
}

void WormWidgets::render(SDL2pp::Renderer& renderer, int worm_state, bool facing_left, int worm_center_x, int worm_center_y, int worm_top_y, int worm_botom_y) {
    int worm_text_x = worm_center_x - (this->worm_text.GetWidth() / 2);
    int worm_text_y = worm_top_y - this->worm_text.GetHeight() - 5;
    int army_text_x = worm_center_x - (this->army_text.GetWidth() / 2);
    int army_text_y = worm_top_y - this->army_text.GetHeight() - this->worm_text.GetHeight() - 10;
    int health_text_x = worm_center_x - (this->health_text.GetWidth() / 2);
    int health_text_y = worm_botom_y + 5;

    SDL2pp::Texture health_text_texture(renderer, this->health_text);
    
    renderer.SetDrawColor(BLACK);
    renderTextBackground(renderer, worm_text_x, worm_text_y, this->worm_text);
    renderTextBackground(renderer, army_text_x, army_text_y, this->army_text);
    renderTextBackground(renderer, health_text_x, health_text_y, health_text_texture);
    
    renderer.SetDrawColor(WHITE);
    renderText(renderer, worm_text_x, worm_text_y, this->worm_text);
    renderText(renderer, army_text_x, army_text_y, this->army_text);
    renderText(renderer, health_text_x, health_text_y, health_text_texture);
    
    if (worm_state == AIMING) {
        handleAimingState(renderer, facing_left, worm_center_x, worm_center_y);
    }
}

void WormWidgets::renderTextBackground(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text) {
    renderer.FillRect(SDL2pp::Rect(x, y, text.GetWidth(), text.GetHeight()));
}

void WormWidgets::renderText(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text) {
    renderer.Copy(text, SDL2pp::NullOpt, SDL2pp::Rect(x, y, text.GetWidth(), text.GetHeight()));
}

void WormWidgets::handleAimingState(SDL2pp::Renderer& renderer, bool facing_left, int worm_center_x, int worm_center_y) {
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    int distance_from_worm_center_x = std::round(cos(std::abs(this->crosshair_angle)*M_PI/180)*CROSSHAIR_DISTANCE_FROM_WORM_CENTER);
    int distance_from_worm_center_y = std::round(sin(std::abs(this->crosshair_angle)*M_PI/180)*CROSSHAIR_DISTANCE_FROM_WORM_CENTER);
    if(this->crosshair_angle > 0) {
        distance_from_worm_center_y *= -1;
    }
    if(facing_left) {
        distance_from_worm_center_x *= -1;
    }
    crosshair_x = distance_from_worm_center_x;
    crosshair_y = distance_from_worm_center_y;
    this->crosshair_an.render(renderer, SDL2pp::Rect(worm_center_x + distance_from_worm_center_x - this->crosshair_an.get_frame_size()/2, worm_center_y + distance_from_worm_center_y - this->crosshair_an.get_frame_size()/2, this->crosshair_an.get_frame_size(), this->crosshair_an.get_frame_size()), flip);
}

int WormWidgets::get_crosshair_x() {
    return this->crosshair_x/RESOLUTION_MULTIPLIER;
}

int WormWidgets::get_crosshair_y() {
    return this->crosshair_y/RESOLUTION_MULTIPLIER;
}