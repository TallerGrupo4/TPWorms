#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <exception>
#include <iostream>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>
#include <thread>

#include "action.h"
#include "worm.h"
#include "match.h"
#include "client.h"
#include "surfaces.h"
#include "constantes_cliente.h"

class MatchRenderer {
private:
    Client& client;
    MatchSurfaces surfaces;

    bool handleEvents(Match& match);

    void render(SDL2pp::Renderer& renderer, Match& match);

    void update(Match& match, std::chrono::duration<double> dt);

public:
    explicit MatchRenderer(Client& client);

    int start();
};
#endif  // MATCH_RENDERER_H
