#include "colordependentwidgets.h"

ArmyColorDependentMisc::ArmyColorDependentMisc(SDL2pp::Surface& crosshair, SDL_Color worm_color) : crosshair(crosshair), worm_color(worm_color) {}

SDL_Color ArmyColorDependentMisc::get_worm_color() {
    return this->worm_color;
}

SDL2pp::Surface& ArmyColorDependentMisc::get_crosshair() {
    return this->crosshair;
}
