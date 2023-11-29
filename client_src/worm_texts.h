#ifndef WORM_SURFACES_H
#define WORM_SURFACES_H

#include <string>
#include <map>
#include <cmath>
#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "constantes_cliente.h"
#include "colordependentwidgets.h"

class WormSpecificTexts {
private:
    SDL_Color player_color;
    Animation crosshair_an;
    int crosshair_angle;
    SDL2pp::Texture army_text;
    SDL2pp::Texture worm_text;
    SDL2pp::Surface health_text;
public:
    explicit WormSpecificTexts(SDL2pp::Renderer& renderer, char army_id, ArmyColorDependentMisc widgets, char worm_id, int health_points, int max_health);
    void update_health(int health_points, int max_health);
    void update_crosshair(int angle);
    void render(SDL2pp::Renderer& renderer, int worm_state, bool facing_left, int worm_center_x, int worm_center_y, int worm_top_y, int worm_botom_y);
};

#endif  // WORM_SURFACES_H