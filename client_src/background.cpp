#include "background.h"

Background::Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : bkgrnd_image(SDL2pp::Texture(renderer,surfaces.background1)), width(map_width), height(map_height) {
    for (size_t i = 0; i < platforms.size(); i++) {
        this->beams.push_back(Beam(platforms[i],surfaces,renderer,map_width,map_height));
    }
}

void Background::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    SDL2pp::Rect source_rect(0,0,bkgrnd_image.GetWidth(),bkgrnd_image.GetHeight());
    SDL2pp::Rect dest_rect(0,0,renderer.GetLogicalWidth(),renderer.GetLogicalHeight());
    renderer.Copy(
        bkgrnd_image,
        source_rect,
        dest_rect,
        0.0,              // don't rotate
        SDL2pp::NullOpt);

    for (size_t i = 0; i < beams.size(); i++) {
        beams[i].render(renderer, camera_offset_x, camera_offset_y);
    }
}

int Background::get_map_width() {
    return this->width;
}

int Background::get_map_height() {
    return this->height;
}