#include "match_renderer.h"
#include <memory>
#include <algorithm>
#include "Animation.h"
#include "../common_src/clock.h"

using namespace SDL2pp;

MatchRenderer::MatchRenderer(Client& client, Snapshot map_received) : client(client), sdl(SDL_INIT_VIDEO), ttf(),
                window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE),
                renderer(window, -1, SDL_RENDERER_ACCELERATED) {
        renderer.SetLogicalSize(window.GetWidth(), window.GetHeight());
        SDL_WarpMouseInWindow(window.Get(),window.GetWidth()/2,window.GetHeight()/2);
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
                        SDL_WarpMouseInWindow(window.Get(), match.get_turn_worm_x() + window.GetWidth()/2 - mouse_motion_x, match.get_turn_worm_y() + window.GetHeight()/2 - mouse_motion_y);
                        match.update_camera(mouse_motion_x, mouse_motion_y, true, true);
                        mouse_motion_x = 0;
                        mouse_motion_y = 0;
                        break;
                    }
                    case SDLK_q:
                        return false;
                    case SDLK_LEFT: {
                        if (match.handle_left_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_RIGHT: {
                        if (match.handle_right_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_UP: {
                        if (match.handle_up_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if (match.handle_down_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_RETURN: {
                        if (match.handle_enter_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_BACKSPACE: {
                        if (match.handle_backspace_button(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                    case SDLK_SPACE: {
                        std::cout << "Entre al space pressed\n";
                        if (match.handle_space_button_pressed(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                }
            }  // Fin KEY_DOWN
            break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    // case SDLK_LEFT:
                    //     action = std::make_shared<ActionMovLeft>();
                    //     client.send_action(action);
                    //     //player.stopMoving();
                    //     break;
                    // case SDLK_RIGHT:
                    //     action = std::make_shared<ActionMovRight>();
                    //     client.send_action(action);
                    //     //player.stopMoving();
                    //     break;
                    case SDLK_SPACE: {
                        std::cout << "Entre al space release\n";
                        if (match.handle_space_button_release(action)) {
                            client.send_action(action);
                        }
                        break;
                    }
                }
            }  // Fin KEY_UP
            break;
            case SDL_MOUSEMOTION: {
                //std::cout << "\n\nDID ENTER IN SDL_MOUSEMOTION\n" << std::endl;
                SDL_MouseMotionEvent& mouseMotionEvent = (SDL_MouseMotionEvent&)event;
                std::cout << "x:" << mouseMotionEvent.x << " y: " << mouseMotionEvent.y << std::endl;
                match.handle_mouse_motion(mouseMotionEvent.x , mouseMotionEvent.y);
                //window.GetHeight()/2
                mouse_motion_x += mouseMotionEvent.xrel;
                mouse_motion_y += mouseMotionEvent.yrel;
                //std::cout << "x relative:" << mouse_motion_x << " y relative: " << mouse_motion_y << std::endl;
                match.update_camera(mouse_motion_x, mouse_motion_y, false, false, true);
                break;
            }
            case SDL_MOUSEWHEEL: {
                SDL_MouseWheelEvent& MouseWheelEvent = (SDL_MouseWheelEvent&)event;
                if (MouseWheelEvent.y > 0) {
                    if (match.handle_mouse_scroll_up(action)) {
                        client.send_action(action);
                    }
                } else if (MouseWheelEvent.y < 0) {
                    if (match.handle_mouse_scroll_down(action)) {
                        client.send_action(action);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                SDL_MouseButtonEvent& mouseButtonEvent = (SDL_MouseButtonEvent&)event;
                switch (mouseButtonEvent.button) {
                case SDL_BUTTON_LEFT:
                    match.handle_mouse_left_click(mouseButtonEvent.x, mouseButtonEvent.y);
                    break;
                case SDL_BUTTON_RIGHT:
                    if (match.handle_mouse_right_click(action, mouseButtonEvent.x, mouseButtonEvent.y)) {
                        client.send_action(action);
                    }
                    break;
                default:
                    break;
                }
                std::cout << "x:" << mouseButtonEvent.x << " y: " << mouseButtonEvent.y << std::endl;
                break;
            }
            case SDL_QUIT: {
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
            match.update_from_snapshot(snapshot, surfaces, renderer);
        }
        
        match.update_from_iter(iter);
        render(renderer, match);
    } catch (std::exception& e) {

        // If case of error, print it and exit with error
        std::cerr<< "Uknown execption catched in Main thread, match_renderer " << e.what() << std::endl;
    }
}

void MatchRenderer::start() {
    client.start();
    Clock clock(std::bind(&MatchRenderer::execute_and_update, this, std::placeholders::_1), FRAME_TIME, running);
    clock.tick();
    // std::cout << "MatchRenderer::start() finished" << std::endl;
    client.exit();
    // std::cout << "MatchRenderer::start() client.exit() finished" << std::endl;
}