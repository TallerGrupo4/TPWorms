#include "background.h"

Background::Background(std::vector<PlatformSnapshot> platforms, int map_width, int map_height,
                       int water_level, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer):
        bkgrnd_image(SDL2pp::Texture(renderer, surfaces.background1)),
        water_an(renderer, surfaces.water, MILISECS_FOR_WATER),
        width(map_width),
        height(map_height),
        water_level(water_level) {
    for (size_t i = 0; i < platforms.size(); i++) {
        this->beams.push_back(Beam(platforms[i], surfaces, renderer, map_width, map_height));
    }
}

void Background::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    SDL2pp::Rect source_rect(0, 0, bkgrnd_image.GetWidth(), bkgrnd_image.GetHeight());
    SDL2pp::Rect dest_rect(0, 0, renderer.GetLogicalWidth(), renderer.GetLogicalHeight());
    renderer.Copy(bkgrnd_image, source_rect, dest_rect, 0.0, SDL2pp::NullOpt);

    for (size_t i = 0; i < beams.size(); i++) {
        beams[i].render(renderer, camera_offset_x, camera_offset_y);
    }
}

void Background::render_water(SDL2pp::Renderer& renderer, int camera_offset_x,
                              int camera_offset_y) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    int water_pos_y = ((-1) * water_level * RESOLUTION_MULTIPLIER) +
                      (renderer.GetLogicalHeight() / 2) - WATER_ABOVE_OFFSET * 2;
    int water_parts_width = water_an.get_frame_size();
    int start_pos_x = 0;
    int times_to_render_waves = (renderer.GetLogicalWidth() / water_parts_width);
    while (start_pos_x < times_to_render_waves * water_parts_width) {
        this->water_an.render(renderer,
                              SDL2pp::Rect(start_pos_x, water_pos_y - camera_offset_y,
                                           water_parts_width, water_an.get_frame_size()),
                              flip);
        start_pos_x += water_parts_width;
    }
    int sea_pos_y = water_pos_y + water_parts_width;
    renderer.SetDrawColor(DARK_BLUE);
    renderer.FillRect(SDL2pp::Rect(0, sea_pos_y - camera_offset_y, renderer.GetLogicalWidth(),
                                   height + sea_pos_y));
    renderer.SetDrawColor(WHITE);
}

void Background::update_water() { this->water_an.update_once(); }

int Background::get_map_width() { return this->width; }

int Background::get_map_height() { return this->height; }
