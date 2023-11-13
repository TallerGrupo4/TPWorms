#include "beam.h"

Beam::Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    // if (pltfrm.type) {
    //     if (pltfrm.angle) {
    //         /* code */
    //     }
        
    // }
    switch (pltfrm.type) {
        case LargeVertical :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_vertical);
        break;
        case Large65 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_65);
        break;
        case Large45 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_45);
        break;
        case Large25 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_25);
        break;
        case LargeHorizontal :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_horizontal);
        break;
        case LargeMinus25 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_m_25);
        break;
        case LargeMinus45 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_m_45);
        break;
        case LargeMinus65 :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_m_65);
        break;
        case LargeVerticalFlipped :
        beam_image = SDL2pp::Texture(renderer, surfaces.large_beam_vertical_flipped);
        break;
        case ShortVertical :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_vertical);
        break;
        case Short65 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_65);
        break;
        case Short45 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_45);
        break;
        case Short25 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_25);
        break;
        case ShortHorizontal :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_horizontal);
        break;
        case ShortMinus25 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_m_25);
        break;
        case ShortMinus45 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_m_45);
        break;
        case ShortMinus65 :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_m_65);
        break;
        case ShortVerticalFlipped :
        beam_image = SDL2pp::Texture(renderer, surfaces.short_beam_vertical_flipped);
        break;
    }
    this->type = pltfrm.type;
    this->x = pltfrm.pos_x;
    this->y = pltfrm.pos_y;
}

void Beam::render(SDL2pp::Renderer& renderer) {
    SDL2pp::Rect source_rect(0,0,beam_image.GetWidth(),beam_image.GetHeight());
    SDL2pp::Rect dest_rect(x,y,width,height);

    renderer.Copy(
        beam_image,
        source_rect,
        dest_rect,
        0.0,              // don't rotate
        SDL2pp::NullOpt);
}