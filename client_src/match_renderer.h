#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <exception>
#include <iostream>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>
#include <thread>

#include "../common_src/clock.h"

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
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    Match match;
    bool running = true;

    bool handleEvents(Match& match);

    void render(SDL2pp::Renderer& renderer, Match& match);

public:
    explicit MatchRenderer(Client& client);

    void start();
    
    void execute_and_update(int iter);
};
#endif  // MATCH_RENDERER_H
