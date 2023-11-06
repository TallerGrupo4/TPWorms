#include "match_renderer.h"

using namespace SDL2pp;

bool MatchRenderer::handleEvents(Player& player) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return false;
                    case SDLK_LEFT:
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        player.moveRigth();
                        break;
                }
            }  // Fin KEY_DOWN
            break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        player.stopMoving();
                        break;
                }
            }  // Fin KEY_UP
            break;
            case SDL_MOUSEMOTION:
                // std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        }  // fin switch(event)
    }      // fin while(SDL_PollEvents)
    return true;
}

void MatchRenderer::render(SDL2pp::Renderer& renderer, Player& player) {
    renderer.SetDrawColor(0x80, 0x80, 0x80);
    renderer.Clear();
    player.render(renderer);
    renderer.Present();
}

void MatchRenderer::update(Player& player, float dt) { player.update(dt); }

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
        Texture worm_sprite(renderer, Surface(WORM_WALK_SPRITES).SetColorKey(true, 0));
        Player player(worm_sprite, true, false);
        bool running = true;
        // Game state
        while (running) {
            running = handleEvents(player);
            update(player, FRAME_RATE);
            render(renderer, player);
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
