#ifndef WORM_WIDGETS_H
#define WORM_WIDGETS_H

#include <cmath>
#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "client_constants.h"
#include "colordependentwidgets.h"

class WormWidgets {
private:
    SDL_Color player_color;
    Animation crosshair_an;
    int crosshair_angle;
    int crosshair_x;
    int crosshair_y;
    SDL2pp::Texture army_text;
    SDL2pp::Texture worm_text;
    SDL2pp::Surface health_text;

    void renderTextBackground(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text);
    void renderText(SDL2pp::Renderer& renderer, int x, int y, SDL2pp::Texture& text);
    void handleAimingState(SDL2pp::Renderer& renderer, bool facing_left, int worm_center_x,
                           int worm_center_y);

public:
    explicit WormWidgets(SDL2pp::Renderer& renderer, char army_id,
                         ArmyColorDependentWidgets widgets, char worm_id, int health_points,
                         int max_health);
    void update_health(int health_points, int max_health);
    void update_crosshair(int angle);
    void update_crosshair_from_iter();
    void render(SDL2pp::Renderer& renderer, int worm_state, bool facing_left, int worm_center_x,
                int worm_center_y, int worm_top_y, int worm_botom_y);
    int get_crosshair_x();
    int get_crosshair_y();
};

#endif  // WORM_WIDGETS_H
