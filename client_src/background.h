#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"

#include "Animation.h"
#include "beam.h"
#include "surfaces.h"

class Background {
private:
    std::vector<Beam> beams;
    SDL2pp::Texture bkgrnd_image;
    Animation water_an;
    int width;
    int height;
    int water_level;

public:
    explicit Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height,
                        int water_level, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    void render_water(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    void update_water();
    int get_map_width();
    int get_map_height();
};

#endif  // BACKGROUND_H
