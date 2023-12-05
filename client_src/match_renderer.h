#ifndef MATCH_RENDERER_H
#define MATCH_RENDERER_H

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/clock.h"
#include "../common_src/custom_errors.h"

#include "actions.h"
#include "client.h"
#include "client_constants.h"
#include "match.h"
#include "surfaces.h"
#include "worm.h"

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

    bool handleEvents(Match& match);

    void render(SDL2pp::Renderer& renderer, Match& match);

public:
    explicit MatchRenderer(Client& client, const Snapshot& map_received);

    void start();

    void execute_and_update(int iter);
};
#endif  // MATCH_RENDERER_H
