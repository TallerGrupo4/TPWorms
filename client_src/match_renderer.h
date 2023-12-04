#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <exception>
#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <SDL2pp/SDL2pp.hh>
#include <thread>

#include "../common_src/clock.h"

#include "actions.h"
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
    SDL2pp::SDLTTF ttf;
    SDL2pp::Mixer mixer;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    Match match;
    bool running = true;
    int mouse_motion_x = 0;
    int mouse_motion_y = 0;
    // std::map<char, std::vector<char>> my_army;
    // uint8_t worm_turn_id = 0;

    bool handleEvents(Match& match);

    void render(SDL2pp::Renderer& renderer, Match& match);

public:
    explicit MatchRenderer(Client& client, Snapshot map_received);

    void start();
    
    void execute_and_update(int iter);
};
#endif  // MATCH_RENDERER_H
