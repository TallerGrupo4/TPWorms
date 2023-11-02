#include <iostream>
#include <exception>
#include <unistd.h>

#include "Player.h"

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;
class MatchRenderer {
private:
    bool handleEvents(Player &player);

    void render(SDL2pp::Renderer &renderer, Player &player);

    void update(Player &player, float dt);

public:
    int start();
};
