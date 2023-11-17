#include "background.h"

Background::Background() {}

Background::Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : width(map_width), height(map_height) {
    for (size_t i = 0; i < platforms.size(); i++) {
        this->beams.push_back(Beam(platforms[i],surfaces,renderer,map_width,map_height));
    }
}

void Background::render(SDL2pp::Renderer& renderer) {
    for (size_t i = 0; i < beams.size(); i++) {
        beams[i].render(renderer);
    }
}

int Background::get_map_width() {
    return this->width;
}

int Background::get_map_height() {
    return this->height;
}