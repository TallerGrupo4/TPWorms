#include "match_renderer.h"
#include <memory>
#include "Animation.h"
#include "../common_src/clock.h"

using namespace SDL2pp;

MatchRenderer::MatchRenderer(Client& client, Snapshot map_received) : client(client), sdl(SDL_INIT_VIDEO),
                window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE),
                renderer(window, -1, SDL_RENDERER_ACCELERATED) {
        renderer.SetLogicalSize(window.GetWidth(), window.GetHeight());
        SDL_WarpMouseInWindow(window.Get(),window.GetWidth()/2,window.GetHeight()/2);
        std::cout << "match height: " << map_received.height << "\n match width: " << map_received.width << std::endl;
        match = Match(map_received,surfaces,renderer);
        this->render(renderer,match);
}

bool MatchRenderer::handleEvents(Match& match) {
    SDL_Event event;
    std::shared_ptr<Action> action;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_ESCAPE: {
                        camera_activated = camera_activated ? false : true;
                        SDL_WarpMouseInWindow(window.Get(),window.GetWidth()/2 - mouse_motion_x,window.GetHeight()/2 - mouse_motion_y);
                        mouse_motion_x = 0;
                        mouse_motion_y = 0;
                        match.update_camera(mouse_motion_x, mouse_motion_y, true);
                        break;
                        // return false;
                    }
                    case SDLK_q:
                        return false;
                    case SDLK_LEFT: {
                        action = std::make_shared<ActionMovLeft>();
                        // action->get_type() = 0;
                        client.send_action(action);
                        //client.push_game_command(game_command);
                        //player.moveLeft();
                        break;
                    }
                    case SDLK_RIGHT:
                        action = std::make_shared<ActionMovRight>();
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
                        action = std::make_shared<ActionMovLeft>();
                        client.send_action(action);
                        //player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        action = std::make_shared<ActionMovRight>();
                        client.send_action(action);
                        //player.stopMoving();
                        break;
                }
            }  // Fin KEY_UP
            break;
            case SDL_MOUSEMOTION: {
                if(camera_activated) {
                    //std::cout << "\n\nDID ENTER IN SDL_MOUSEMOTION\n" << std::endl;
                    SDL_MouseMotionEvent& mouseMotionEvent = (SDL_MouseMotionEvent&)event;
                    mouse_motion_x += mouseMotionEvent.xrel;
                    mouse_motion_y += mouseMotionEvent.yrel;
                    //std::cout << "x relative:" << mouse_motion_x << " y relative: " << mouse_motion_y << std::endl;
                    match.update_camera(mouse_motion_x,mouse_motion_y);
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                SDL_MouseButtonEvent& mouseButtonEvent = (SDL_MouseButtonEvent&)event;
                std::cout << "x:" << mouseButtonEvent.x << " y: " << mouseButtonEvent.y << std::endl;
                break;
            }
            case SDL_QUIT: {
                std::cout << "Quit :(" << std::endl;
                return false;
            }
        }  // fin switch(event)
    }      // fin while(SDL_PollEvents)
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
        std::cerr<< "Uknown execption catched in Main thread, match_renderer " << e.what() << std::endl;
    }
}

void MatchRenderer::start() {
    client.start();
    Clock clock(std::bind(&MatchRenderer::execute_and_update, this, std::placeholders::_1), FRAME_TIME, running);
    clock.tick();
}