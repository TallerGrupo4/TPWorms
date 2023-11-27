#ifndef PARSER_SERVER_H
#define PARSER_SERVER_H

class ParserServer {

private:
    float apply_multiplier(float& x);

public:
    ParserServer() = default;

    void parse_map_dimensions(float& width, float& height, float& worm_width, float& worm_height);

    void parse_platform_mesures(float& x, float& y, float& width, float& height);

    void parse_worm_mesures(float& x, float& y);

    void parse_projectile_mesures(float& x, float& y, float& angle);

    ~ParserServer() = default;
};

#endif  // PARSER_SERVER_H
