#include "match_renderer.h"
#include <memory>
#include "Animation.h"
#include "../common_src/clock.h"

using namespace SDL2pp;

MatchRenderer::MatchRenderer(Client& client) : client(client), sdl(SDL_INIT_VIDEO),
                window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE),
                renderer(window, -1, SDL_RENDERER_ACCELERATED) {
        Snapshot snapshot = client.recv_map();
        // Snapshot snpsht;
        // while (client.recv_snapshot(snpsht);
        // snapshot.worms = snpsht.worms;
        std::cout << "match height: " << snapshot.height << "\n match width: " << snapshot.width << std::endl;
        match = Match(snapshot,surfaces,renderer);
        this->render(renderer,match);
}

bool MatchRenderer::handleEvents(Match& match) {
    SDL_Event event;
    std::shared_ptr<Action> action;
    // Action action;
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
                        // action.movement_x = 10;
                        action->movement_x = 10;
                        // action.type = 0;
                        action->type = 0;
                        client.send_action(action);
                        //client.push_game_command(game_command);
                        //player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        // action.movement_x = 10;
                        action->movement_x = 10;
                        // action.type = 1;
                        action->type = 1;
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
                        // action.movement_x = 0;
                        action->movement_x = 0;
                        // action.type = 0;
                        action->type = 0;
                        client.send_action(action);
                        //player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        // action.movement_x = 0;
                        action->movement_x = 0;
                        // action.type = 1;
                        action->type = 1;
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



void MatchRenderer::execute_and_update(int iter) {
    try {
        running = handleEvents(match);
        Snapshot snapshot;
        while (client.recv_snapshot(snapshot)) {
            match.update_from_snapshot(snapshot);
        }
        
            //while
                // Snapshot snpsht = client.recv_snapshot();
                // match.update(snpsht,elapsed_time);
                // //update(match, elapsed_time);
            // Snapshot snapsht;
            // client.recv_snapshot(snapshot);
            // match.update(snpsht,elapsed_time); // iter / FPS
            match.update_from_iter(iter); // iter
            render(renderer, match);

            //Snapshot snapshot;

            // !!!!!!!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!!!!
            /*
            while (client.recv_snapshot(snapshot)) {
                update(snapshot);
            }
            update(FRAME_RATE); // Animations will advance now
            render(); // Render the game
            sleep(FRAME_RATE);
            */
            // !!!!!!!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!!!!

            // THIS CODE IS WRONG -----
            // Snapshot snapshot = client.pop_snapshot();
            // render(renderer, player);
            // THIS CODE IS WRONG -----
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
    }
}

void MatchRenderer::start() {
    Clock clock(std::bind(&MatchRenderer::execute_and_update, this, std::placeholders::_1), FRAME_TIME, running);
    clock.tick();
}