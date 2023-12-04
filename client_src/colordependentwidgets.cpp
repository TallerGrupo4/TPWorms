#include "colordependentwidgets.h"

ArmyColorDependentWidgets::ArmyColorDependentWidgets(SDL2pp::Surface& crosshair, SDL_Color worm_color) : crosshair(crosshair), worm_color(worm_color) {}

SDL_Color ArmyColorDependentWidgets::get_worm_color() {
    return this->worm_color;
}

SDL2pp::Surface& ArmyColorDependentWidgets::get_crosshair() {
    return this->crosshair;
}
