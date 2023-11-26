#ifndef HUD_H
#define HUD_H

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

class Hud {
private:
    Target target;
    SDL2pp::Surface turn_time_text;
public:
    explicit Hud(Target target, uint turn_time);
    void update_target(Target target);
    void update_turn_time_text(uint turn_time);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // HUD_H