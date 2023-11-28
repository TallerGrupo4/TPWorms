#ifndef WORM_SURFACES_H
#define WORM_SURFACES_H

#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

class WormSpecificTexts {
private:
    SDL_Color player_color;
    SDL2pp::Texture army_text;
    SDL2pp::Texture worm_text;
    SDL2pp::Surface health_text;
public:
    explicit WormSpecificTexts(SDL2pp::Renderer& renderer, char army_id, SDL_Color player_color, char worm_id, int health_points, int max_health);
    void update_health(int health_points, int max_health);
    void render(SDL2pp::Renderer& renderer, int worm_center_x, int worm_top_y, int worm_botomm_y);
};

#endif  // WORM_SURFACES_H