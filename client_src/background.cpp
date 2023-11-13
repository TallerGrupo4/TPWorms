#include "background.h"

Background::(std::vector<PlatformSnapshot> platforms, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    for (PlatformSnapshot pltfrm : platforms){
        Beam beam(pltfrm, surfaces, renderer);
        this->beams.push_back(beam);
    }
}