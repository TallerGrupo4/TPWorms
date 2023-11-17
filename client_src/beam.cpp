#include "beam.h"
#include <iostream>

Beam::Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, int map_width, int map_height) : beam_image(assign_texture(pltfrm,surfaces,renderer)) {
    this->type = pltfrm.type;
    std::cout << "x de la viga recibido: " << pltfrm.pos_x << " y de la viga recibido: " << pltfrm.pos_y << std::endl;
    assign_positions(renderer, pltfrm.pos_x, pltfrm.pos_y, map_width, map_height);
}

void Beam::render(SDL2pp::Renderer& renderer) {
    SDL2pp::Rect source_rect(0,0,beam_image.GetWidth(),beam_image.GetHeight());
    SDL2pp::Rect dest_rect(x,y,width,height);
    std::cout << "x de la viga: " << x << " y de la viga: " << y << " width de la viga : " << width << " height de la viga: " << height << std::endl;

    renderer.Copy(
        beam_image,
        source_rect,
        dest_rect,
        0.0,              // don't rotate
        SDL2pp::NullOpt);
}

void Beam::assign_positions(SDL2pp::Renderer& renderer, int x, int y, int map_width, int map_height) {
    int top_left_x = 0;
    int top_left_y = 0;
    this->width = 140*RESOLUTION_MULTIPLIER;
    this->height = 20*RESOLUTION_MULTIPLIER;
    switch (this->type) {
        case LargeVertical :
        top_left_x = x-BEAM_LARGE_VERTICAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_VERTICAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case Large65 :
        top_left_x = x-BEAM_LARGE_65_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_65_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case Large45 :
        top_left_x = x-BEAM_LARGE_45_CENTER*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_45_CENTER*RESOLUTION_MULTIPLIER;
        break;
        case Large25 :
        top_left_x = x-BEAM_LARGE_25_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_25_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case LargeHorizontal :
        top_left_x = x-BEAM_LARGE_HORIZONTAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_HORIZONTAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case LargeMinus25 :
        top_left_x = x-BEAM_LARGE_MINUS_25_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_MINUS_25_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case LargeMinus45 :
        top_left_x = x-BEAM_LARGE_45_CENTER*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_45_CENTER*RESOLUTION_MULTIPLIER;
        break;
        case LargeMinus65 :
        top_left_x = x-BEAM_LARGE_MINUS_65_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_MINUS_65_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case LargeVerticalFlipped :
        top_left_x = x-BEAM_LARGE_VERTICAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_VERTICAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case ShortVertical :
        top_left_x = x-BEAM_SHORT_VERTICAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_VERTICAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case Short65 :
        top_left_x = x-BEAM_SHORT_65_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_65_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case Short45 :
        top_left_x = x-BEAM_SHORT_45_CENTER*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_45_CENTER*RESOLUTION_MULTIPLIER;
        break;
        case Short25 :
        top_left_x = x-BEAM_SHORT_25_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_25_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case ShortHorizontal :
        top_left_x = x-BEAM_SHORT_HORIZONTAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_HORIZONTAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case ShortMinus25 :
        top_left_x = x-BEAM_SHORT_M_25_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_M_25_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case ShortMinus45 :
        top_left_x = x-BEAM_SHORT_45_CENTER*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_45_CENTER*RESOLUTION_MULTIPLIER;
        break;
        case ShortMinus65 :
        top_left_x = x-BEAM_SHORT_M_65_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_SHORT_M_65_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
        case ShortVerticalFlipped :
        top_left_x = x-BEAM_LARGE_VERTICAL_CENTER_X*RESOLUTION_MULTIPLIER;
        top_left_y = y-BEAM_LARGE_VERTICAL_CENTER_Y*RESOLUTION_MULTIPLIER;
        break;
    }
    this->x = top_left_x + (int)(renderer.GetLogicalWidth()/2);
    this->y = top_left_y + (int)(renderer.GetLogicalHeight()/2);
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