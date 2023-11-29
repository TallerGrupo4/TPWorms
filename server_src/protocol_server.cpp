#include "protocol_server.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>
#include <sys/types.h>

#include "../common_src/liberror.h"

ProtocolServer::ProtocolServer(Socket& socket, ParserServer& parser): socket(socket), parser(parser) {}

// ------------------------------ PUBLIC METHODS ------------------------------

void ProtocolServer::send_command(const Command& command) {
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char code[1] = {command.get_code()};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        // throw
    }
    switch (code[0]) {
        case CASE_JOIN: {
            send_match_id(command.get_match_id());
            send_map_names(command.get_map_names());
            send_number_of_players(command.get_number_of_players());
            break;
        }
        case CASE_CREATE: {
            send_match_id(command.get_match_id());
            send_map_names(command.get_map_names());
            send_number_of_players(command.get_number_of_players());
            break;
        }
        case CASE_MATCH_NOT_FOUND: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_LIST: {
            send_list(command.get_available_matches());
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_MATCH_FULL: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_MATCH_ALREADY_STARTED: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_NUMBER_OF_PLAYERS: {
            send_match_id(command.get_match_id());
            send_number_of_players(command.get_number_of_players());
            break;
        }
        default:
            break;
    }
}

const Command ProtocolServer::recv_command() {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        // throw
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    switch (code[0]) {
        case CASE_CREATE: {
            return recv_create(code);
        }
        case CASE_JOIN: {
            return recv_join(code);
        }
        case CASE_LIST: {
            return recv_list(code);
        }
        case CASE_START: {
            uint match_id = recv_match_id();
            std::string map_name = recv_map_name();
            return Command(code[0], match_id, map_name);
        }
        case CASE_NUMBER_OF_PLAYERS: {
            return Command(code[0], DEFAULT);;
        }
        default:
            // Handle error
            break;
    }
    // Handle error
    return Command(DEFAULT, DEFAULT);
}

int ProtocolServer::send_snapshot(Snapshot& snapshot) {
    if (send_map_dimensions(snapshot.map_dimensions.width, snapshot.map_dimensions.height, snapshot.map_dimensions.worm_width, snapshot.map_dimensions.worm_height, snapshot.map_dimensions.amount_of_worms, snapshot.map_dimensions.water_level) < 0) {
        return SOCKET_FAILED;
    }
    if (send_platforms(snapshot.platforms) < 0) {
        return SOCKET_FAILED;
    }

    send_army(snapshot.my_army);

    if (send_time_and_worm_turn(snapshot.turn_time_and_worm_turn.turn_time, snapshot.turn_time_and_worm_turn.worm_turn) < 0) {
        return SOCKET_FAILED;
    }
    if (send_worms(snapshot.worms) < 0) {
        return SOCKET_FAILED;
    }

    send_projectiles(snapshot.projectiles);

    send_end_game(snapshot.get_end_game());

    return 1;
}

std::shared_ptr<GameCommand> ProtocolServer::recv_game_command() {
    uint8_t worm_id[1];
    socket.recvall(worm_id, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char code[1];
    socket.recvall(code, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    switch (code[0]) {
        case MOV: {
            return recv_mov(worm_id[0]);
        }
        case JUMP: {
            return recv_jump(worm_id[0]);
        }
        case AIM: {
            return recv_aim(worm_id[0]);
        }
        case SHOOT: {
            return recv_shoot(worm_id[0]);
        }
        case CHANGE_TOOL: {
            return recv_change_tool(worm_id[0]);
        }
        default:
            // Dummy GameCommand, it does nothing (or maybe it says that the client has disconnected?).
            return std::make_shared<GameCommand>();
    }
}


// ------------------------------ PRIVATE METHODS ------------------------------

std::shared_ptr<GameCommand> ProtocolServer::recv_mov(uint8_t& worm_id) {
    char movement_x[1];
    socket.recvall(movement_x, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    return std::make_shared<MoveCommand>(worm_id, movement_x[0]);
}

std::shared_ptr<GameCommand> ProtocolServer::recv_jump(uint8_t& worm_id) {
    char movement_x[1];
    socket.recvall(movement_x, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    return std::make_shared<JumpCommand>(worm_id, movement_x[0]);
}

std::shared_ptr<GameCommand> ProtocolServer::recv_aim(uint8_t& worm_id) {
    char look_direction_x[1];
    socket.recvall(look_direction_x, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char look_direction_y[1];
    socket.recvall(look_direction_y, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }

    return std::make_shared<AimCommand>(look_direction_x[0], look_direction_y[0], worm_id);
}

std::shared_ptr<GameCommand> ProtocolServer::recv_shoot(uint8_t& worm_id) {
    int potency[1];
    socket.recvall(potency, 4, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    potency[0] = ntohl(potency[0]);
    return std::make_shared<UseToolCommand>(worm_id, potency[0], 0, 0, 2 * FPS);
}

std::shared_ptr<GameCommand> ProtocolServer::recv_change_tool(uint8_t& worm_id) {
    char scroll_direction[1];
    socket.recvall(scroll_direction, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    return std::make_shared<ChangeToolCommand>(worm_id, scroll_direction[0]);
}

int ProtocolServer::send_map_dimensions(float& _width, float& _height, float& _worm_width, float& _worm_height, int& _amount_of_worms, int& _water_level) {
    parser.parse_map_dimensions(_width, _height, _worm_width, _worm_height, _water_level);
    int width[1] = {static_cast<int>(_width)};
    int height[1] = {static_cast<int>(_height)};
    int worm_width[1] = {static_cast<int>(_worm_width)};
    int worm_height[1] = {static_cast<int>(_worm_height)};
    int water_level[1] = {_water_level};
    width[0] = htonl(width[0]);
    height[0] = htonl(height[0]);
    worm_width[0] = htonl(worm_width[0]);
    worm_height[0] = htonl(worm_height[0]);
    water_level[0] = htonl(water_level[0]);
    socket.sendall(width, 4, &was_closed);
    socket.sendall(height, 4, &was_closed);
    socket.sendall(worm_width, 4, &was_closed);
    socket.sendall(worm_height, 4, &was_closed);
    socket.sendall(water_level, 4, &was_closed);
    int amount_of_worms[1] = {_amount_of_worms};
    amount_of_worms[0] = htonl(amount_of_worms[0]);
    socket.sendall(amount_of_worms, 4, &was_closed);
    return 1;
}

int ProtocolServer::send_platforms(std::vector<PlatformSnapshot>& platforms) {
    uint16_t num_of_plats[1] = {htons(platforms.size())};
    if (socket.sendall(num_of_plats, 2, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    for (auto& platform : platforms) {
        parser.parse_platform_mesures(platform.pos_x, platform.pos_y, platform.width, platform.height);
        BeamType type[1] = {platform.type};
        if (socket.sendall(type, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_x[1] = {static_cast<int>(platform.pos_x)};
        pos_x[0] = htonl(pos_x[0]);
        if (socket.sendall(pos_x, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_y[1] = {static_cast<int>(platform.pos_y)};
        pos_y[0] = htonl(pos_y[0]);
        if (socket.sendall(pos_y, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int width[1] = {static_cast<int>(platform.width )};
        width[0] = htonl(width[0]);
        if (socket.sendall(width, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int height[1] = {static_cast<int>(platform.height)};
        height[0] = htonl(height[0]);
        if (socket.sendall(height, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
    }
    return 1;
}

void ProtocolServer::send_army(std::map<char, std::vector<char>>& army) {
    uint8_t num_of_teams[1] = {static_cast<uint8_t>(army.size())};
    if (socket.sendall(num_of_teams, 1, &was_closed) < 0) {
        // throw
    }
    for (auto& team : army) {
        // Only one loop because there is only one army
        char army_id[1] = {team.first};
        if (socket.sendall(army_id, 1, &was_closed) < 0) {
            // throw
        }
        char num_of_worms[1] = {static_cast<char>(team.second.size())};
        if (socket.sendall(num_of_worms, 1, &was_closed) < 0) {
            // throw
        }
        for (auto& worm_id : team.second) {
            char id[1] = {worm_id};
            if (socket.sendall(id, 1, &was_closed) < 0) {
                // throw
            }
        }
    }
}

int ProtocolServer::send_time_and_worm_turn(const int& _turn_time, const int& _worm_turn) {
    int turn_time[1] = {_turn_time};
    turn_time[0] = htonl(turn_time[0]);
    if (socket.sendall(turn_time, 4, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    int worm_turn[1] = {_worm_turn};
    worm_turn[0] = htonl(worm_turn[0]);
    if (socket.sendall(worm_turn, 4, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    return 1;
}

int ProtocolServer::send_worms(std::vector<WormSnapshot>& worms) {
    uint16_t num_of_worms[1] = {htons(worms.size())};
    if (socket.sendall(num_of_worms, 2, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    for (auto& worm : worms) {
        parser.parse_worm_mesures(worm.pos_x, worm.pos_y);
        char id[1] = {worm.id};
        if (socket.sendall(id, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_x[1] = {static_cast<int>(worm.pos_x)};
        pos_x[0] = htonl(pos_x[0]);
        if (socket.sendall(pos_x, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_y[1] = {static_cast<int>(worm.pos_y)};
        pos_y[0] = htonl(pos_y[0]);
        if (socket.sendall(pos_y, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int angle[1] = {worm.angle};
        angle[0] = htonl(angle[0]);
        if (socket.sendall(angle, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int max_health[1] = {worm.max_health};
        max_health[0] = htonl(max_health[0]);
        if (socket.sendall(max_health, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int health[1] = {worm.health};
        health[0] = htonl(health[0]);
        if (socket.sendall(health, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        char direction[1] = {worm.direction};
        if (socket.sendall(direction, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int weapon[1] = {worm.weapon};
        weapon[0] = htonl(weapon[0]);
        if (socket.sendall(weapon, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int state[1] = {worm.state};
        state[0] = htonl(state[0]);
        if (socket.sendall(state, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        char team_id[1] = {worm.team_id};
        if (socket.sendall(team_id, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int aiming_angle[1] = {worm.aiming_angle};
        aiming_angle[0] = htonl(aiming_angle[0]);
        if (socket.sendall(aiming_angle, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
    }
    return 1;
}

void ProtocolServer::send_projectiles(std::vector<ProjectileSnapshot>& projectiles) {
    uint8_t num_of_projectiles[1] = {static_cast<uint8_t>(projectiles.size())};
    socket.sendall(num_of_projectiles, 1, &was_closed);
    for (auto& projectile : projectiles) {
        parser.parse_projectile_mesures(projectile.pos_x, projectile.pos_y, projectile.angle, projectile.radius);
        int pos_x[1] = {static_cast<int>(projectile.pos_x)};
        pos_x[0] = htonl(pos_x[0]);
        socket.sendall(pos_x, 4, &was_closed);
        int pos_y[1] = {static_cast<int>(projectile.pos_y)};
        pos_y[0] = htonl(pos_y[0]);
        socket.sendall(pos_y, 4, &was_closed);
        int angle[1] = {static_cast<int>(projectile.angle)};
        angle[0] = htonl(angle[0]);
        socket.sendall(angle, 4, &was_closed);
        char type[1] = {projectile.type};
        socket.sendall(type, 1, &was_closed);
        int direction[1] = {projectile.direction};
        direction[0] = htonl(direction[0]);
        socket.sendall(direction, 4, &was_closed);
        int state[1] = {projectile.state};
        state[0] = htonl(state[0]);
        socket.sendall(state, 4, &was_closed);
        char id[1] = {projectile.id};
        socket.sendall(id, 1, &was_closed);
        int explosion_type[1] = {projectile.explosion_type};
        explosion_type[0] = htonl(explosion_type[0]);
        socket.sendall(explosion_type, 4, &was_closed);
        int radius[1] = {static_cast<int>(projectile.radius)};
        radius[0] = htonl(radius[0]);
        socket.sendall(radius, 4, &was_closed);

    }
}



const Command ProtocolServer::recv_create(const char* code) {
    const uint match_id = recv_match_id();
    return Command(code[0], match_id);
}

const Command ProtocolServer::recv_join(const char* code) {
    const uint match_id = recv_match_id();
    return Command(code[0], match_id);
}

const std::string ProtocolServer::recv_map_name() {
    uint16_t map_name_size[1];
    socket.recvall(map_name_size, 2, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    map_name_size[0] = ntohs(map_name_size[0]);
    std::vector<char> map_name(map_name_size[0]);
    socket.recvall(map_name.data(), map_name_size[0], &was_closed);
    if (was_closed) {
        // throw
    }
    std::string map_name_str(map_name.begin(), map_name.end());
    return map_name_str;
}

const uint ProtocolServer::recv_match_id() {
    uint match_id[1];
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        // throw
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    match_id[0] = ntohl(match_id[0]);
    return match_id[0];
}

const Command ProtocolServer::recv_list(const char* code) {
    return Command(code[0], DEFAULT);
}

void ProtocolServer::send_match_id(const uint _match_id) {
    uint match_id[1] = {_match_id};
    match_id[0] = htonl(match_id[0]);
    socket.sendall(match_id, 4, &was_closed);
}

void ProtocolServer::send_map_names(const std::vector<std::string>& map_names) {
    uint16_t num_of_maps[1] = {htons(static_cast<uint16_t>(map_names.size()))};
    socket.sendall(num_of_maps, 2, &was_closed);
    for (auto& map_name : map_names) {
        uint16_t map_name_size[1] = {htons(static_cast<uint16_t>(map_name.size()))};
        socket.sendall(map_name_size, 2, &was_closed);
        socket.sendall(map_name.c_str(), map_name.size(), &was_closed);
    }
}

void ProtocolServer::send_number_of_players(const uint8_t number_of_players) {
    uint8_t num_of_players[1] = {number_of_players};
    socket.sendall(num_of_players, 1, &was_closed);
}

void ProtocolServer::send_list(const std::map<uint, std::string>& matches_availables) {
    uint8_t num_of_matches[1] = {static_cast<uint8_t>(matches_availables.size())};
    socket.sendall(num_of_matches, 1, &was_closed);
    for (auto& match : matches_availables) {
        uint match_id[1] = {match.first};
        match_id[0] = htonl(match_id[0]);
        if (socket.sendall(match_id, 4, &was_closed) < 0) {
            // throw
        }
        uint8_t map_name_size[1] = {static_cast<uint8_t>(match.second.size())};
        if (socket.sendall(map_name_size, 1, &was_closed) < 0) {
            // throw
        }
        if (socket.sendall(match.second.c_str(), match.second.size(), &was_closed) < 0) {
            // throw
        }
    }
}

void ProtocolServer::send_map_name(const std::string map_name) {
    uint16_t map_name_size[1] = {htons(static_cast<uint16_t>(map_name.size()))};
    socket.sendall(map_name_size, 2, &was_closed);
    socket.sendall(map_name.c_str(), map_name.size(), &was_closed);
}

void ProtocolServer::send_end_game(bool end_game) {
    char end_game_code[1] = {end_game};
    socket.sendall(end_game_code, 1, &was_closed);
}
