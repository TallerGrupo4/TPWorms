#include "beam.h"

Beam::Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer,
           int map_width, int map_height):
        beam_image(assign_texture(pltfrm, surfaces, renderer)) {
    this->type = pltfrm.type;
    this->width = pltfrm.width * RESOLUTION_MULTIPLIER;
    this->height = pltfrm.height * RESOLUTION_MULTIPLIER;
    this->x = pltfrm.pos_x * RESOLUTION_MULTIPLIER - width / 2;
    this->y = 0 - pltfrm.pos_y * RESOLUTION_MULTIPLIER - height / 2;
}

void Beam::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    SDL2pp::Rect source_rect(0, 0, beam_image.GetWidth(), beam_image.GetHeight());
    SDL2pp::Rect dest_rect(x + (int)(renderer.GetLogicalWidth() / 2) - camera_offset_x,
                           y + (int)(renderer.GetLogicalHeight() / 2) - camera_offset_y, width,
                           height);
    renderer.Copy(beam_image, source_rect, dest_rect, 0.0, SDL2pp::NullOpt);
}

SDL2pp::Texture Beam::assign_texture(PlatformSnapshot pltfrm, MatchSurfaces& surfaces,
                                     SDL2pp::Renderer& renderer) {
    SDL2pp::Texture texture(renderer, surfaces.large_beam_vertical);  // Default large beam
    switch (pltfrm.type) {
        case LargeVertical:
            break;
        case Large65:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_65);
            break;
        case Large45:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_45);
            break;
        case Large25:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_25);
            break;
        case LargeHorizontal:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_horizontal);
            break;
        case LargeMinus25:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_25);
            break;
        case LargeMinus45:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_45);
            break;
        case LargeMinus65:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_65);
            break;
        case LargeVerticalFlipped:
            texture = SDL2pp::Texture(renderer, surfaces.large_beam_vertical_flipped);
            break;
        case ShortVertical:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_vertical);
            break;
        case Short65:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_65);
            break;
        case Short45:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_45);
            break;
        case Short25:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_25);
            break;
        case ShortHorizontal:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_horizontal);
            break;
        case ShortMinus25:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_25);
            break;
        case ShortMinus45:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_45);
            break;
        case ShortMinus65:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_65);
            break;
        case ShortVerticalFlipped:
            texture = SDL2pp::Texture(renderer, surfaces.short_beam_vertical_flipped);
            break;
    }
    return texture;
}
