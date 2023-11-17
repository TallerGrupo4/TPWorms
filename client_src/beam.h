#ifndef BEAM_H
#define BEAM_H

#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "surfaces.h"
#include "beam.h"

class Beam {
private:
    SDL2pp::Texture beam_image;
    BeamType type;
    int x;
    int y;
    int width;
    int height;

    SDL2pp::Texture assign_texture(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void assign_positions(int x, int y, int map_width, int map_height);
public:
    explicit Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, int map_width, int map_height);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // BEAM_H