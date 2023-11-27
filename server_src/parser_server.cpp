#include <cmath>
#include <sstream>
#include <string>
#include "parser_server.h"
#include "../common_src/constants.h"


float ParserServer::apply_multiplier(float& x) {
    return std::round(x * MULTIPLIER);
}

void ParserServer::parse_map_dimensions(float& width, float& height, float& worm_width, float& worm_height) {
    width = apply_multiplier(width);
    height = apply_multiplier(height);
    worm_width = apply_multiplier(worm_width);
    worm_height = apply_multiplier(worm_height);
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

void ParserServer::parse_projectile_mesures(float& x, float& y, float& angle) {
    x = apply_multiplier(x);
    y = apply_multiplier(y);
    angle = apply_multiplier(angle);
}



// void ParserServer::parse_sending_command(Command& command) {
//     switch (command.code) {
//         // This does not make any sense. It is for future parsing...?
//         case CASE_JOIN: {
//             command.code = CASE_JOIN;
//             break;
//         }
//         case CASE_CREATE: {
//             command.code = CASE_CREATE;
//             break;
//         }
//         default:
//             break;
//     }
// }

// void ParserServer::parse_sending_snapshot(Snapshot& snapshot) {
//     switch (command.code) {
//         // This does not make any sense. It is for future parsing...?
//         case CASE_CHAT: {
//             command.code = CASE_CHAT;
//             break;
//         }
//         default:
//             break;
//     }
// }
