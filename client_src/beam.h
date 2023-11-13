#ifndef BEAM_H
#define BEAM_H

#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "surfaces.h"
#include "beam.h"

enum BeamType {
    LargeVertical,
    Large65,
    Large45,
    Large25,
    LargeHorizontal,
    LargeMinus25,
    LargeMinus45,
    LargeMinus65,
    LargeVerticalFlipped,
    ShortVertical,
    Short65,
    Short45,
    Short25,
    ShortHorizontal,
    ShortMinus25,
    ShortMinus45,
    ShortMinus65,
    ShortVerticalFlipped,
};

class Beam {
private:
    SDL2pp::Texture beam_image;
    BeamType type;
    int x;
    int y;
    int width;
    int height;

    SDL2pp::Texture assign_texture(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
public:
    explicit Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // BEAM_H