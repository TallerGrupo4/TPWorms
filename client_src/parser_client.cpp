#include "parser_client.h"

#include <iostream>
#include <sstream>
#include <string>


float ParserClient::apply_pix_per_meter_and_multiplier(float& value) {
    return std::round(value * PIX_PER_METER / MULTIPLIER);
}

bool ParserClient::get_degree_of_beam_type(BeamType type, int& degree) {
    switch (type) {
        case LargeVertical:
            return false;
        case Large65:
            degree = 65;
            return true;
        case Large45:
            degree = 45;
            return true;
        case Large25:
            degree = 25;
            return true;
        case LargeHorizontal:
            return false;
        case LargeMinus25:
            degree = 25;
            return true;
        case LargeMinus45:
            degree = 45;
            return true;
        case LargeMinus65: 
            degree = 65;
            return true;
        case LargeVerticalFlipped:
            return false;
        case ShortVertical:
            return false;
        case Short65:
            degree = 65;
            return true;
        case Short45:
            degree = 45;
            return true;
        case Short25:
            degree = 25;
            return true;
        case ShortHorizontal:
            return false;
        case ShortMinus25:
            degree = 25;
            return true;
        case ShortMinus45:
            degree = 45;
            return true;
        case ShortMinus65:
            degree = 65;
            return true;
        case ShortVerticalFlipped:
            return false;
        default:
            return false;
    }
}

int ParserClient::calculate_beam_width(int degree, float beam_actual_height, float beam_actual_width) {
    return round(beam_actual_height*sin(degree*M_PI/180)+beam_actual_width*cos(degree*M_PI/180));
}

int ParserClient::calculate_beam_height(int degree, float beam_actual_height, float beam_actual_width) {
    return round(beam_actual_height*cos(degree*M_PI/180)+beam_actual_width*sin(degree*M_PI/180));
}

void ParserClient::parse_platform_mesures(float& x, float& y, float& width, float& height) {
    x = apply_pix_per_meter_and_multiplier(x);
    y = apply_pix_per_meter_and_multiplier(y);
    width = apply_pix_per_meter_and_multiplier(width);
    height = apply_pix_per_meter_and_multiplier(height);
}

void ParserClient::parse_map_dimensions(float& width, float& height, float& worm_width, float& worm_height, int& water_level) {
    width = apply_pix_per_meter_and_multiplier(width);
    height = apply_pix_per_meter_and_multiplier(height);
    worm_width = apply_pix_per_meter_and_multiplier(worm_width);
    worm_height = apply_pix_per_meter_and_multiplier(worm_height);
    water_level = (water_level * PIX_PER_METER) / MULTIPLIER;
}

void ParserClient::parse_worm(float& x, float& y) {
    x = apply_pix_per_meter_and_multiplier(x);
    y = apply_pix_per_meter_and_multiplier(y);
}

void ParserClient::parse_projectile_mesures(float& x, float& y, float& angle, float& radius) {
    x = apply_pix_per_meter_and_multiplier(x);
    y = apply_pix_per_meter_and_multiplier(y);
    angle = std::round(angle / MULTIPLIER);
    radius = apply_pix_per_meter_and_multiplier(radius);
}

void ParserClient::parse_provision_box_mesures(float& x, float& y, float& width, float& height) {
    x = apply_pix_per_meter_and_multiplier(x);
    y = apply_pix_per_meter_and_multiplier(y);
    width = apply_pix_per_meter_and_multiplier(width);
    height = apply_pix_per_meter_and_multiplier(height);
}
