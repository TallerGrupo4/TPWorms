#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <exception>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>

#include "Player.h"
#include "constantes_cliente.h"

using namespace SDL2pp;
class MatchRenderer {
private:
    bool handleEvents(Player& player);

    void render(SDL2pp::Renderer& renderer, Player& player);

    void update(Player& player, float dt);

public:
    int start();
};
#endif  // MATCH_RENDERER_H
