#include "background.h"

Background::Background(std::vector<PlatformSnapshot> platforms, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    for (PlatformSnapshot pltfrm : platforms){
        Beam beam(pltfrm, surfaces, renderer);
        this->beams.push_back(beam);
    }
}

void Background::render(SDL2pp::Renderer& renderer) {
    for (std::list<Beam>::iterator it = beams.begin(); it != beams.end(); ++it) {
        it->render(renderer);
    }
}