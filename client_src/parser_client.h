#include <vector>

#include "../common_src/constants.h"

#ifndef PARSER_CLIENT_H
#define PARSER_CLIENT_H

class ParserClient {

private:
    float apply_pix_per_meter_and_multiplier(const float& value);


public:
    ParserClient() = default;

    void parse_platform_mesures(float& x, float& y, float& width, float& height);

    void parse_map_dimensions(float& width, float& height, float& worm_width, float& worm_height,
                              int& water_level);

    int calculate_beam_width(int degree, float beam_actual_height, float beam_actual_width);

    int calculate_beam_height(int degree, float beam_actual_height, float beam_actual_width);

    bool get_degree_of_beam_type(BeamType type, int& degree);

    void parse_projectile_mesures(float& x, float& y, float& angle, float& radius);

    void parse_worm(float& x, float& y);

    void parse_provision_box_mesures(float& x, float& y, float& width, float& height);

    ~ParserClient() = default;
};

#endif  // PARSER_CLIENT_H
