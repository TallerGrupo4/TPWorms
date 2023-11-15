#include "background.h"

Background::Background() {}

Background::Background(std::vector<PlatformSnapshot> platforms, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    for (size_t i = 0; i < platforms.size(); i++) {
        this->beams.push_back(Beam(platforms[i],surfaces,renderer));
    }
}

void Background::render(SDL2pp::Renderer& renderer) {
    for (size_t i = 0; i < beams.size(); i++) {
        beams[i].render(renderer);
    }
}