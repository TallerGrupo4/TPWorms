#include "parser_server.h"

#include <cmath>
#include <sstream>
#include <string>

#include "../common_src/constants.h"


float ParserServer::apply_multiplier(const float& x) { return std::round(x * MULTIPLIER); }

void ParserServer::parse_map_dimensions(float& width, float& height, float& worm_width,
                                        float& worm_height, int& water_level) {
    width = apply_multiplier(width);
    height = apply_multiplier(height);
    worm_width = apply_multiplier(worm_width);
    worm_height = apply_multiplier(worm_height);
    water_level = water_level * MULTIPLIER;
}

void ParserServer::parse_platform_mesures(float& x, float& y, float& width, float& height) {
    x = apply_multiplier(x);
    y = apply_multiplier(y);
    width = apply_multiplier(width);
    height = apply_multiplier(height);
}


void ParserServer::parse_worm_mesures(float& x, float& y) {
    x = apply_multiplier(x);
    y = apply_multiplier(y);
}

void ParserServer::parse_projectile_mesures(float& x, float& y, float& angle, float& radius) {
    x = apply_multiplier(x);
    y = apply_multiplier(y);
    angle = apply_multiplier(angle);
    radius = apply_multiplier(radius);
}

void ParserServer::parse_provision_box_mesures(float& x, float& y, float& width, float& height) {
    x = apply_multiplier(x);
    y = apply_multiplier(y);
    width = apply_multiplier(width);
    height = apply_multiplier(height);
}

void ParserServer::parse_position_form_shoot(float& x, float& y) {
    x = std::round((x * MULTIPLIER) / PIX_PER_METER) / MULTIPLIER;
    y = std::round((-y * MULTIPLIER) / PIX_PER_METER) / MULTIPLIER;
}
