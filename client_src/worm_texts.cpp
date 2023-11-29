#include "worm_texts.h"

WormSpecificTexts::WormSpecificTexts(SDL2pp::Renderer& renderer, char army_id, ArmyColorDependentMisc widgets, char worm_id, int health_points, int max_health) :
    player_color(widgets.get_worm_color()),
    crosshair_an(renderer, widgets.get_crosshair(), SECS_FOR_CROSSHAIR_SPRITES),
    crosshair_angle(0),
    army_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Player " + std::to_string(army_id+1)), player_color)),
    worm_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Worm " + std::to_string(worm_id+1)), player_color)),
    health_text(SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string(std::to_string(health_points) + "/" + std::to_string(max_health)), player_color)) {}

void WormSpecificTexts::update_health(int health_points, int max_health) {
    std::string health_text_str = std::to_string(health_points) + "/" + std::to_string(max_health);
    SDL2pp::Font worm_text_font(WORMS_FONT_PATH, WORM_FONT_SIZE);
    this->health_text = worm_text_font.RenderText_Blended(health_text_str, player_color);
}

void WormSpecificTexts::update_crosshair(int angle) {
    this->crosshair_angle = angle;
}

void WormSpecificTexts::render(SDL2pp::Renderer& renderer, int worm_state, bool facing_left, int worm_center_x, int worm_center_y, int worm_top_y, int worm_botom_y) {
    int worm_text_x = worm_center_x - (this->worm_text.GetWidth() / 2);
    int worm_text_y = worm_top_y - this->worm_text.GetHeight() - 5;
    int army_text_x = worm_center_x - (this->army_text.GetWidth() / 2);
    int army_text_y = worm_top_y - this->army_text.GetHeight() - this->worm_text.GetHeight() - 10;
    int health_text_x = worm_center_x - (this->health_text.GetWidth() / 2);
    int health_text_y = worm_botom_y + 5;
    SDL2pp::Texture health_text_texture(renderer, this->health_text);
    renderer.SetDrawColor({0,0,0});
    renderer.FillRect(SDL2pp::Rect(worm_text_x, worm_text_y, this->worm_text.GetWidth(), this->worm_text.GetHeight()));
    renderer.FillRect(SDL2pp::Rect(army_text_x, army_text_y, this->army_text.GetWidth(), this->army_text.GetHeight()));
    renderer.FillRect(SDL2pp::Rect(health_text_x, health_text_y, this->health_text.GetWidth(), this->health_text.GetHeight()));
    renderer.SetDrawColor({255,255,255});
    renderer.Copy(this->worm_text, SDL2pp::NullOpt, SDL2pp::Rect(worm_text_x, worm_text_y, this->worm_text.GetWidth(), this->worm_text.GetHeight()));
    renderer.Copy(this->army_text, SDL2pp::NullOpt, SDL2pp::Rect(army_text_x, army_text_y, this->army_text.GetWidth(), this->army_text.GetHeight()));
    renderer.Copy(health_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(health_text_x, health_text_y, this->health_text.GetWidth(), this->health_text.GetHeight()));
    if (worm_state == AIMING) {
        SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        int distance_from_worm_center_x = std::round(cos(std::abs(this->crosshair_angle)*M_PI/180)*CROSSHAIR_DISTANCE_FROM_WORM_CENTER);
        int distance_from_worm_center_y = std::round(sin(std::abs(this->crosshair_angle*M_PI/180))*CROSSHAIR_DISTANCE_FROM_WORM_CENTER);
        if(this->crosshair_angle > 0) {
            distance_from_worm_center_y *= -1;
        }
        if(facing_left) {
            distance_from_worm_center_x *= -1;
        }
        this->crosshair_an.render(renderer, SDL2pp::Rect(worm_center_x + distance_from_worm_center_x - this->crosshair_an.get_frame_size()/2, worm_center_y + distance_from_worm_center_y - this->crosshair_an.get_frame_size()/2, this->crosshair_an.get_frame_size(), this->crosshair_an.get_frame_size()), flip);
    }
}