#ifndef COLOR_WIDGETS_H
#define COLOR_WIDGETS_H

#include <SDL2pp/SDL2pp.hh>

class ArmyColorDependentWidgets {
private:
    SDL2pp::Surface& crosshair;
    SDL_Color worm_color;

public:
    ArmyColorDependentWidgets(SDL2pp::Surface& crosshair, SDL_Color worm_color);
    SDL_Color get_worm_color();
    SDL2pp::Surface& get_crosshair();
};

#endif  // COLOR_WIDGETS_H
