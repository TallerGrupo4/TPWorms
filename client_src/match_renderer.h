#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <exception>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>

#include "Player.h"
#include "client.h"
#include "surfaces.h"
#include "constantes_cliente.h"

class MatchRenderer {
private:
    Client& client;
    MatchSurfaces surfaces;

    bool handleEvents(Player& player);

    void render(SDL2pp::Renderer& renderer, Player& player);

    void update(Player& player, float dt);

public:
    explicit MatchRenderer(Client& client);

    int start();
};
#endif  // MATCH_RENDERER_H
