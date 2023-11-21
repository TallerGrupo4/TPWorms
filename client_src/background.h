#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "surfaces.h"
#include "beam.h"

class Background {
private:
    std::vector<Beam> beams;
    SDL2pp::Texture bkgrnd_image;
    int width;
    int height;

public:
    explicit Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    int get_map_width();
    int get_map_height();
};

#endif  // BACKGROUND_H