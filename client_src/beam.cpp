#include "beam.h"
#include <iostream>

Beam::Beam(PlatformSnapshot pltfrm, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, int map_width, int map_height) : beam_image(assign_texture(pltfrm,surfaces,renderer)) {
    this->type = pltfrm.type;
    std::cout << "x de la viga recibido: " << pltfrm.pos_x << " y de la viga recibido: " << pltfrm.pos_y << std::endl;
    assign_positions(renderer, pltfrm.pos_x, pltfrm.pos_y, map_width, map_height);
}

void Beam::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    SDL2pp::Rect source_rect(0,0,beam_image.GetWidth(),beam_image.GetHeight());
    std::cout << " width de la imagen de la viga : " << beam_image.GetWidth() << " height de la imagen de laviga: " << beam_image.GetHeight() << std::endl;
    SDL2pp::Rect dest_rect(x+(int)(renderer.GetLogicalWidth()/2) - camera_offset_x,y+(int)(renderer.GetLogicalHeight()/2) - camera_offset_y,width,height);
    std::cout << "x de la viga: " << x+(int)(renderer.GetLogicalWidth()/2) << " y de la viga: " << y+(int)(renderer.GetLogicalHeight()/2) << " width de la viga : " << width << " height de la viga: " << height << std::endl;

    renderer.Copy(
        beam_image,
        source_rect,
        dest_rect,
        0.0,              // don't rotate
        SDL2pp::NullOpt);
}

int Beam::calculate_beam_width(int degree, float beam_actual_height, float beam_actual_width) {
    return round(beam_actual_height*sin(degree*M_PI/180)+beam_actual_width*cos(degree*M_PI/180))*PIX_PER_METER;
}

int Beam::calculate_beam_height(int degree, float beam_actual_height, float beam_actual_width) {
    return round(beam_actual_height*cos(degree*M_PI/180)+beam_actual_width*sin(degree*M_PI/180))*PIX_PER_METER;
}

void Beam::assign_positions(SDL2pp::Renderer& renderer, int x, int y, int map_width, int map_height) {
    int top_left_x = x;
    int top_left_y = 0-y;
    switch (this->type) {
        case LargeVertical :
        top_left_x =- BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y =- BEAM_LARGE_VERTICAL_CENTER_Y;
        this->width = round(PLAT_HEIGHT)*PIX_PER_METER;
        this->height = round(PLAT_BIG)*PIX_PER_METER;
        break;
        case Large65 :
        top_left_x =- BEAM_LARGE_65_CENTER_X;
        top_left_y =- BEAM_LARGE_65_CENTER_Y;
        this->width = calculate_beam_width(65,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(65,PLAT_HEIGHT,PLAT_BIG);
        break;
        case Large45 :
        top_left_x =- BEAM_LARGE_45_CENTER;
        top_left_y =- BEAM_LARGE_45_CENTER;
        this->width = calculate_beam_width(45,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(45,PLAT_HEIGHT,PLAT_BIG);
        break;
        case Large25 :
        top_left_x =- BEAM_LARGE_25_CENTER_X;
        top_left_y =- BEAM_LARGE_25_CENTER_Y;
        this->width = calculate_beam_width(25,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(25,PLAT_HEIGHT,PLAT_BIG);
        break;
        case LargeHorizontal :
        top_left_x =- PLAT_BIG*PIX_PER_METER/2;//BEAM_LARGE_HORIZONTAL_CENTER_X;
        top_left_y =- PLAT_HEIGHT*PIX_PER_METER/2;//BEAM_LARGE_HORIZONTAL_CENTER_Y;
        this->width = PLAT_BIG*PIX_PER_METER;
        this->height = PLAT_HEIGHT*PIX_PER_METER;
        break;
        case LargeMinus25 :
        top_left_x =- BEAM_LARGE_MINUS_25_CENTER_X;
        top_left_y =- BEAM_LARGE_MINUS_25_CENTER_Y;
        this->width = calculate_beam_width(25,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(25,PLAT_HEIGHT,PLAT_BIG);
        break;
        case LargeMinus45 :
        top_left_x =- BEAM_LARGE_45_CENTER;
        top_left_y =- BEAM_LARGE_45_CENTER;
        this->width = calculate_beam_width(45,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(45,PLAT_HEIGHT,PLAT_BIG);
        break;
        case LargeMinus65 :
        top_left_x =- BEAM_LARGE_MINUS_65_CENTER_X;
        top_left_y =- BEAM_LARGE_MINUS_65_CENTER_Y;
        this->width = calculate_beam_width(65,PLAT_HEIGHT,PLAT_BIG);
        this->height = calculate_beam_height(65,PLAT_HEIGHT,PLAT_BIG);
        break;
        case LargeVerticalFlipped :
        top_left_x =- BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y =- BEAM_LARGE_VERTICAL_CENTER_Y;
        this->width = round(PLAT_HEIGHT)*PIX_PER_METER;
        this->height = round(PLAT_BIG)*PIX_PER_METER;
        break;
        case ShortVertical :
        top_left_x =- BEAM_SHORT_VERTICAL_CENTER_X;
        top_left_y =- BEAM_SHORT_VERTICAL_CENTER_Y;
        this->width = round(PLAT_HEIGHT)*PIX_PER_METER;
        this->height = round(PLAT_SMALL)*PIX_PER_METER;
        break;
        case Short65 :
        top_left_x =- BEAM_SHORT_65_CENTER_X;
        top_left_y =- BEAM_SHORT_65_CENTER_Y;
        this->width = calculate_beam_width(65,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(65,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case Short45 :
        top_left_x =- BEAM_SHORT_45_CENTER;
        top_left_y =- BEAM_SHORT_45_CENTER;
        this->width = calculate_beam_width(45,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(45,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case Short25 :
        top_left_x =- BEAM_SHORT_25_CENTER_X;
        top_left_y =- BEAM_SHORT_25_CENTER_Y;
        this->width = calculate_beam_width(25,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(25,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case ShortHorizontal :
        top_left_x =- BEAM_SHORT_HORIZONTAL_CENTER_X;
        top_left_y =- BEAM_SHORT_HORIZONTAL_CENTER_Y;
        this->width = round(PLAT_SMALL)*PIX_PER_METER;
        this->height = round(PLAT_HEIGHT)*PIX_PER_METER;
        break;
        case ShortMinus25 :
        top_left_x =- BEAM_SHORT_M_25_CENTER_X;
        top_left_y =- BEAM_SHORT_M_25_CENTER_Y;
        this->width = calculate_beam_width(25,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(25,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case ShortMinus45 :
        top_left_x =- BEAM_SHORT_45_CENTER;
        top_left_y =- BEAM_SHORT_45_CENTER;
        this->width = calculate_beam_width(45,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(45,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case ShortMinus65 :
        top_left_x =- BEAM_SHORT_M_65_CENTER_X;
        top_left_y =- BEAM_SHORT_M_65_CENTER_Y;
        this->width = calculate_beam_width(65,PLAT_HEIGHT,PLAT_SMALL);
        this->height = calculate_beam_height(65,PLAT_HEIGHT,PLAT_SMALL);
        break;
        case ShortVerticalFlipped :
        top_left_x =- BEAM_LARGE_VERTICAL_CENTER_X;
        top_left_y =- BEAM_LARGE_VERTICAL_CENTER_Y;
        this->width = round(PLAT_HEIGHT)*PIX_PER_METER;
        this->height = round(PLAT_SMALL)*PIX_PER_METER;
        break;
    }
    this->x = top_left_x*RESOLUTION_MULTIPLIER;
    this->y = top_left_y*RESOLUTION_MULTIPLIER;
    this->width *= RESOLUTION_MULTIPLIER;
    this->height *= RESOLUTION_MULTIPLIER;
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