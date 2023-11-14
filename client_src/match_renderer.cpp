#include "match_renderer.h"
#include <memory>

using namespace SDL2pp;

MatchRenderer::MatchRenderer(Client& client) : client(client) {}

bool MatchRenderer::handleEvents(Match& match) {
    SDL_Event event;
    // std::shared_ptr<Action> action;
    Action action;
    while (SDL_PollEvent(&event)) {
        //bool is_moving_right;
        //bool is_moving_left;
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return false;
                    case SDLK_LEFT:
                        action.movement_x = 10;
                        action.type = 0;
                        client.send_action(action);
                        //client.push_game_command(game_command);
                        //player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        action.movement_x = 10;
                        action.type = 1;
                        client.send_action(action);
                        //client.push_game_command(game_command);
                        //player.moveRigth();
                        break;
                }
            }  // Fin KEY_DOWN
            break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        action.movement_x = 0;
                        action.type = 0;
                        client.send_action(action);
                        //player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        action.movement_x = 0;
                        action.type = 1;
                        client.send_action(action);
                        //player.stopMoving();
                        break;
                }
            }  // Fin KEY_UP
            break;
            case SDL_MOUSEMOTION:
                // SDL_MouseMotionEvent& mouseMotionEvent = (SDL_MouseMotionEvent&)event;
                // SDL_GetRelativeMouseMode()
                // SDL_SetRelativeMouseMode()
                //mouseMotionEvent.xrel
                // std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        }  // fin switch(event)
    }      // fin while(SDL_PollEvents)
    // client.push_game_command(game_command);
    return true;
}

void MatchRenderer::render(SDL2pp::Renderer& renderer, Match& match) {
    renderer.SetDrawColor(0x80, 0x80, 0x80);
    renderer.Clear();
    match.render(renderer);
    renderer.Present();
}

void MatchRenderer::update(Match& match, std::chrono::duration<double> dt) {}//{ match.update(dt); }

int MatchRenderer::start() {
    try {
        // Initialize SDL library
        SDL sdl(SDL_INIT_VIDEO);

        // Create main window: 800x600 dimensions, resizable, "SDL2pp demo" title
        Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                      SDL_WINDOW_RESIZABLE);

        // Create accelerated video renderer with default driver
        Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Load sprites image as a new texture
        Match match(client.recv_snapshot(),surfaces,renderer);
        //Texture worm_sprite(renderer, surfaces.walking_worm);
        //Worm player(worm_sprite, true, false);
        auto last_frame_time = std::chrono::high_resolution_clock::now();

        bool running = true;
        // Game state
        while (running) {
            auto start = std::chrono::high_resolution_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(start - last_frame_time);

            running = handleEvents(match);
            //while
                // Snapshot snpsht = client.recv_snapshot();
                // match.update(snpsht,elapsed_time);
                // //update(match, elapsed_time);
            Snapshot snpsht = client.recv_snapshot();
            match.update(snpsht,elapsed_time);
            render(renderer, match);
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            last_frame_time = start;
        }
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
