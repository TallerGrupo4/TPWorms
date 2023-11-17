#include "beam.h"

Beam::Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, int map_width, int map_height) : beam_image(assign_texture(pltfrm,surfaces,renderer)) {
    this->type = pltfrm.type;
    assign_positions(pltfrm.pos_x, pltfrm.pos_y, map_width, map_height);
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

void Beam::assign_positions(int x, int y, int map_width, int map_height) {
    int top_left_x = 0;
    int top_left_y = 0;
    switch (this->type) {
        case LargeVertical :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_Y;
        break;
        case Large65 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_65_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_65_CENTER_Y;
        break;
        case Large45 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_45_CENTER;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_45_CENTER;
        break;
        case Large25 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_25_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_25_CENTER_Y;
        break;
        case LargeHorizontal :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_HORIZONTAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_HORIZONTAL_CENTER_Y;
        break;
        case LargeMinus25 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_MINUS_25_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_MINUS_25_CENTER_Y;
        break;
        case LargeMinus45 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_45_CENTER;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_45_CENTER;
        break;
        case LargeMinus65 :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_MINUS_65_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_MINUS_65_CENTER_Y;
        break;
        case LargeVerticalFlipped :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_Y;
        break;
        case ShortVertical :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_VERTICAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_VERTICAL_CENTER_Y;
        break;
        case Short65 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_65_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_65_CENTER_Y;
        break;
        case Short45 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_45_CENTER;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_45_CENTER;
        break;
        case Short25 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_25_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_25_CENTER_Y;
        break;
        case ShortHorizontal :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_HORIZONTAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_HORIZONTAL_CENTER_Y;
        break;
        case ShortMinus25 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_M_25_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_M_25_CENTER_Y;
        break;
        case ShortMinus45 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_45_CENTER;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_45_CENTER;
        break;
        case ShortMinus65 :
        top_left_x = (x*PIX_PER_METER)-BEAM_SHORT_M_65_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_SHORT_M_65_CENTER_Y;
        break;
        case ShortVerticalFlipped :
        top_left_x = (x*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y = (y*PIX_PER_METER)-BEAM_LARGE_VERTICAL_CENTER_Y;
        break;
    }
    this->x = top_left_x + (int)(map_width/2);
    this->y = top_left_y + (int)(map_height/2);
}

SDL2pp::Texture Beam::assign_texture(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    SDL2pp::Texture texture(renderer, surfaces.large_beam_vertical); //Default large beam
    switch (pltfrm.type) {
        case LargeVertical :
        break;
        case Large65 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_65);
        break;
        case Large45 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_45);
        break;
        case Large25 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_25);
        break;
        case LargeHorizontal :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_horizontal);
        break;
        case LargeMinus25 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_25);
        break;
        case LargeMinus45 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_45);
        break;
        case LargeMinus65 :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_m_65);
        break;
        case LargeVerticalFlipped :
        texture = SDL2pp::Texture(renderer, surfaces.large_beam_vertical_flipped);
        break;
        case ShortVertical :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_vertical);
        break;
        case Short65 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_65);
        break;
        case Short45 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_45);
        break;
        case Short25 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_25);
        break;
        case ShortHorizontal :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_horizontal);
        break;
        case ShortMinus25 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_25);
        break;
        case ShortMinus45 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_45);
        break;
        case ShortMinus65 :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_m_65);
        break;
        case ShortVerticalFlipped :
        texture = SDL2pp::Texture(renderer, surfaces.short_beam_vertical_flipped);
        break;
    }
    return texture;
}