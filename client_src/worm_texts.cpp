#include "worm_texts.h"

WormSpecificTexts::WormSpecificTexts(SDL2pp::Renderer& renderer, char army_id, SDL_Color player_color, char worm_id, int health_points, int max_health) :
    player_color(player_color),
    army_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Player " + std::to_string(army_id+1)), player_color)),
    worm_text(renderer, SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Worm " + std::to_string(worm_id+1)), player_color)),
    health_text(SDL2pp::Font(WORMS_FONT_PATH, WORM_FONT_SIZE).RenderText_Blended(std::string("Health: " + std::to_string(health_points) + "/" + std::to_string(max_health)), player_color)) {}

void WormSpecificTexts::update_health(int health_points, int max_health) {
    std::string health_text_str = "Health: " + std::to_string(health_points) + "/" + std::to_string(max_health);
    SDL2pp::Font worm_text_font(WORMS_FONT_PATH, WORM_FONT_SIZE);
    this->health_text = worm_text_font.RenderText_Blended(health_text_str, player_color);
}

void WormSpecificTexts::render(SDL2pp::Renderer& renderer, int worm_center_x, int worm_top_y, int worm_botomm_y) {
    int worm_text_x = worm_center_x - (this->worm_text.GetWidth() / 2);
    int worm_text_y = worm_top_y - this->worm_text.GetHeight();
    renderer.Copy(this->worm_text, SDL2pp::NullOpt, SDL2pp::Rect(worm_text_x, worm_text_y, this->worm_text.GetWidth(), this->worm_text.GetHeight()));
    int army_text_x = worm_center_x - (this->army_text.GetWidth() / 2);
    int army_text_y = worm_top_y - this->army_text.GetHeight() - this->worm_text.GetHeight();
    renderer.Copy(this->army_text, SDL2pp::NullOpt, SDL2pp::Rect(army_text_x, army_text_y, this->army_text.GetWidth(), this->army_text.GetHeight()));
    int health_text_x = worm_center_x - (this->health_text.GetWidth() / 2);
    int health_text_y = worm_botomm_y;
    SDL2pp::Texture health_text_texture(renderer, this->health_text);
    renderer.Copy(health_text_texture, SDL2pp::NullOpt, SDL2pp::Rect(health_text_x, health_text_y, this->health_text.GetWidth(), this->health_text.GetHeight()));
}