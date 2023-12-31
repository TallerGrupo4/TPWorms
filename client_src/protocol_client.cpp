#include "protocol_client.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <sys/types.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

ProtocolClient::ProtocolClient(Socket& socket, ParserClient& parser):
        socket(socket), parser(parser) {}

// ------------------------------ PUBLIC ------------------------------

void ProtocolClient::send_command(const Command& command) {
    char code[1] = {command.get_code()};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        throw LostConnection();
    }
    if (code[0] == CASE_JOIN || code[0] == CASE_CREATE) {
        send_match_id(command.get_match_id());
    } else if (code[0] == CASE_START) {
        send_match_id(command.get_match_id());
        send_map_name(command.get_map_name());
    }
}

const Command ProtocolClient::recv_command() {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        throw LostConnection();
    }
    switch (code[0]) {
        case CASE_JOIN: {
            uint match_id[1];
            recv_match_id(match_id);
            std::vector<std::string> maps_available = recv_map_names();
            const uint8_t number_of_players = recv_number_of_players();
            Command command(code[0], match_id[0], maps_available, number_of_players);
            return command;
        }
        case CASE_CREATE: {
            uint match_id[1];
            recv_match_id(match_id);
            std::vector<std::string> maps_available = recv_map_names();
            const uint8_t number_of_players = recv_number_of_players();
            Command command(code[0], match_id[0], maps_available, number_of_players);
            return command;
        }
        case CASE_LIST: {
            std::map<uint, std::string> matches_availables = recv_list();
            return Command(code[0], matches_availables);
        }
        case CASE_MATCH_FULL: {
            uint match_id[1];
            recv_match_id(match_id);
            return Command(code[0], match_id[0]);
        }
        case CASE_EXIT_SERVER: {
            return Command(code[0], DEFAULT);
        }
        case CASE_MATCH_NOT_FOUND: {
            uint match_id[1];
            recv_match_id(match_id);
            return Command(code[0], match_id[0]);
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            uint match_id[1];
            recv_match_id(match_id);
            return Command(code[0], match_id[0]);
        }
        case CASE_NUMBER_OF_PLAYERS: {
            uint match_id[1];
            recv_match_id(match_id);
            uint8_t number_of_players[1];
            recv_number_of_players(number_of_players);
            return Command(code[0], match_id[0], {""}, number_of_players[0]);
        }
        case CASE_MATCH_ALREADY_STARTED: {
            uint match_id[1];
            recv_match_id(match_id);
            return Command(code[0], match_id[0]);
        }
        default:
            break;
    }
    if (was_closed) {
        throw LostConnection();
    }
    // Throw "man in the middle" error
    return Command(DEFAULT, DEFAULT);
}


void ProtocolClient::send_action(std::shared_ptr<Action> action) {
    action->send(socket, was_closed);
}

Snapshot ProtocolClient::recv_snapshot() {
    Snapshot snapshot;
    recv_dimensions(snapshot);
    recv_platforms(snapshot);
    recv_army(snapshot);
    recv_time_and_worm_turn(snapshot);
    recv_worms(snapshot);
    recv_projectiles(snapshot);
    recv_end_game(snapshot);
    recv_provision_boxes(snapshot);
    recv_armies_health(snapshot);
    recv_wind_force(snapshot);
    return snapshot;
}


// ---------------------------------- PRIVATE ----------------------------------

void ProtocolClient::send_match_id(const uint match_id) {
    uint match_id_to_send = htonl(match_id);
    if (socket.sendall(&match_id_to_send, 4, &was_closed) < 0) {
        throw LostConnection();
    }
}

void ProtocolClient::send_map_name(const std::string& map_name) {
    uint16_t len = htons(static_cast<uint16_t>(map_name.size()));
    if (socket.sendall(&len, 2, &was_closed) < 0) {
        throw LostConnection();
    }
    if (socket.sendall(map_name.c_str(), map_name.size(), &was_closed) < 0) {
        throw LostConnection();
    }
}

void ProtocolClient::recv_wind_force(Snapshot& snapshot) {
    int wind_force[1];
    socket.recvall(wind_force, 4, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
    wind_force[0] = ntohl(wind_force[0]);
    snapshot.set_wind_force(wind_force[0]);
}

void ProtocolClient::recv_dimensions(Snapshot& snapshot) {
    int width[1];
    int height[1];
    int worm_width[1];
    int worm_height[1];
    int water_level[1];
    int amount_of_worms[1];
    socket.recvall(width, 4, &was_closed);
    socket.recvall(height, 4, &was_closed);
    socket.recvall(worm_width, 4, &was_closed);
    socket.recvall(worm_height, 4, &was_closed);
    socket.recvall(water_level, 4, &was_closed);
    socket.recvall(amount_of_worms, 4, &was_closed);
    width[0] = ntohl(width[0]);
    height[0] = ntohl(height[0]);
    worm_width[0] = ntohl(worm_width[0]);
    worm_height[0] = ntohl(worm_height[0]);
    water_level[0] = ntohl(water_level[0]);
    amount_of_worms[0] = ntohl(amount_of_worms[0]);
    float _width = static_cast<float>(width[0]);
    float _height = static_cast<float>(height[0]);
    float _worm_width = static_cast<float>(worm_width[0]);
    float _worm_height = static_cast<float>(worm_height[0]);
    int _water_level = water_level[0];
    int _amount_of_worms = amount_of_worms[0];
    parser.parse_map_dimensions(_width, _height, _worm_width, _worm_height, _water_level);
    snapshot.set_dimensions(_height, _width, _worm_width, _worm_height, _amount_of_worms,
                            _water_level);
}

void ProtocolClient::recv_platforms(Snapshot& snapshot) {
    uint16_t num_of_plats[1];
    socket.recvall(num_of_plats, 2, &was_closed);
    if (was_closed)
        throw LostConnection();
    num_of_plats[0] = ntohs(num_of_plats[0]);
    for (int i = 0; i < num_of_plats[0]; i++) {
        BeamType type[1];
        int pos_x[1];
        int pos_y[1];
        int width[1];
        int height[1];
        socket.recvall(type, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_x, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_y, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(width, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(height, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        width[0] = ntohl(width[0]);
        height[0] = ntohl(height[0]);
        float _pos_x = static_cast<float>(pos_x[0]);
        float _pos_y = static_cast<float>(pos_y[0]);
        float _width = static_cast<float>(width[0]);
        float _height = static_cast<float>(height[0]);
        parser.parse_platform_mesures(_pos_x, _pos_y, _width, _height);

        int degree = 0;
        int __height = static_cast<int>(_height);
        int __width = static_cast<int>(_width);
        if (parser.get_degree_of_beam_type(type[0], degree)) {
            int height_recieved = static_cast<int>(_height);
            int width_recieved = static_cast<int>(_width);
            __height = parser.calculate_beam_height(degree, height_recieved, width_recieved);
            __width = parser.calculate_beam_width(degree, height_recieved, width_recieved);
        }

        PlatformSnapshot platform((BeamType(type[0])), _pos_x, _pos_y, __width, __height);
        snapshot.platforms.push_back(platform);
    }
}

void ProtocolClient::recv_army(Snapshot& snapshot) {
    char num_of_armies[1];
    socket.recvall(num_of_armies, 1, &was_closed);
    for (int i = 0; i < num_of_armies[0]; i++) {
        char army_id[1];
        socket.recvall(army_id, 1, &was_closed);
        char num_of_worms[1];
        socket.recvall(num_of_worms, 1, &was_closed);
        for (int j = 0; j < num_of_worms[0]; j++) {
            char worm_id[1];
            socket.recvall(worm_id, 1, &was_closed);
            snapshot.my_army[army_id[0]].push_back(worm_id[0]);
        }
    }
}

void ProtocolClient::recv_projectiles(Snapshot& snapshot) {
    uint8_t num_of_projectiles[1];
    socket.recvall(num_of_projectiles, 1, &was_closed);
    for (int i = 0; i < num_of_projectiles[0]; i++) {
        int pos_x[1];
        int pos_y[1];
        int angle[1];
        char type[1];
        int direction[1];
        int state[1];
        char id[1];
        int explosion_type[1];
        int radius[1];
        socket.recvall(pos_x, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_y, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(angle, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(type, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(direction, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(state, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(id, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(explosion_type, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(radius, 4, &was_closed);
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        angle[0] = ntohl(angle[0]);
        direction[0] = ntohl(direction[0]);
        state[0] = ntohl(state[0]);
        explosion_type[0] = ntohl(explosion_type[0]) * PIX_PER_METER;
        radius[0] = ntohl(radius[0]);
        float _pos_x = static_cast<float>(pos_x[0]);
        float _pos_y = static_cast<float>(pos_y[0]);
        float _angle = static_cast<float>(angle[0]);
        float _radius = static_cast<float>(radius[0]);
        parser.parse_projectile_mesures(_pos_x, _pos_y, _angle, _radius);
        int height = std::round(_radius * 2);
        int width = std::round(_radius * 2);
        ProjectileSnapshot projectile(type[0], _pos_x, _pos_y, _angle, direction[0], _radius,
                                      state[0], id[0], explosion_type[0], width, height);
        snapshot.projectiles.push_back(projectile);
    }
}

void ProtocolClient::recv_time_and_worm_turn(Snapshot& snapshot) {
    int turn_time[1];
    int worm_turn[1];
    socket.recvall(turn_time, 4, &was_closed);
    if (was_closed)
        throw LostConnection();
    socket.recvall(worm_turn, 4, &was_closed);
    if (was_closed)
        throw LostConnection();
    turn_time[0] = ntohl(turn_time[0]);
    worm_turn[0] = ntohl(worm_turn[0]);
    snapshot.turn_time_and_worm_turn.turn_time = turn_time[0];
    snapshot.turn_time_and_worm_turn.worm_turn = worm_turn[0];
}

void ProtocolClient::recv_worms(Snapshot& snapshot) {
    uint16_t num_of_worms[1];
    socket.recvall(num_of_worms, 2, &was_closed);
    if (was_closed)
        throw LostConnection();
    num_of_worms[0] = ntohs(num_of_worms[0]);
    for (int i = 0; i < num_of_worms[0]; i++) {
        char id[1];
        int pos_x[1];
        int pos_y[1];
        int angle[1];
        int max_health[1];
        int health[1];
        char direction[1];
        int weapon[1];
        int state[1];
        char team_id[1];
        int aiming_angle[1];
        int current_ammo[1];
        socket.recvall(id, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_x, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_y, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(angle, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(max_health, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(health, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(direction, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(weapon, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(state, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(team_id, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(aiming_angle, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(current_ammo, 4, &was_closed);
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        float _pos_x = static_cast<float>(pos_x[0]);
        float _pos_y = static_cast<float>(pos_y[0]);
        parser.parse_worm(_pos_x, _pos_y);
        angle[0] = ntohl(angle[0]);
        max_health[0] = ntohl(max_health[0]);
        health[0] = ntohl(health[0]);
        weapon[0] = ntohl(weapon[0]);
        state[0] = ntohl(state[0]);
        aiming_angle[0] = ntohl(aiming_angle[0]);
        current_ammo[0] = ntohl(current_ammo[0]);
        WormSnapshot worm(id[0], _pos_x, _pos_y, angle[0], max_health[0], health[0], direction[0],
                          weapon[0], state[0], team_id[0], aiming_angle[0], current_ammo[0]);
        snapshot.worms.push_back(worm);
    }
}

void ProtocolClient::recv_end_game(Snapshot& snapshot) {
    char end_game[1];
    socket.recvall(end_game, 1, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
    if (end_game[0] == 1 /*true*/) {
        snapshot.set_end_game();
    }
}

void ProtocolClient::recv_provision_boxes(Snapshot& snapshot) {
    uint8_t num_of_provision_boxes[1];
    socket.recvall(num_of_provision_boxes, 1, &was_closed);
    for (int i = 0; i < num_of_provision_boxes[0]; i++) {
        BoxType type[1];
        int pos_x[1];
        int pos_y[1];
        char id[1];
        BoxState state[1];
        int width[1];
        int height[1];
        socket.recvall(type, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_x, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(pos_y, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(id, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(state, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(width, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(height, 4, &was_closed);
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        width[0] = ntohl(width[0]);
        height[0] = ntohl(height[0]);
        float _pos_x = static_cast<float>(pos_x[0]);
        float _pos_y = static_cast<float>(pos_y[0]);
        float _width = static_cast<float>(width[0]);
        float _height = static_cast<float>(height[0]);
        parser.parse_provision_box_mesures(_pos_x, _pos_y, _width, _height);
        ProvisionBoxSnapshot provision_box(type[0], _pos_x, _pos_y, id[0], state[0], _width,
                                           _height);
        snapshot.provision_boxes.push_back(provision_box);
    }
}

void ProtocolClient::recv_armies_health(Snapshot& snapshot) {
    uint8_t num_of_armies[1];
    socket.recvall(num_of_armies, 1, &was_closed);
    if (was_closed)
        throw LostConnection();
    for (int i = 0; i < num_of_armies[0]; i++) {
        char army_id[1];
        int health[1];
        socket.recvall(army_id, 1, &was_closed);
        if (was_closed)
            throw LostConnection();
        socket.recvall(health, 4, &was_closed);
        if (was_closed)
            throw LostConnection();
        health[0] = ntohl(health[0]);
        snapshot.armies_health[army_id[0]] = health[0];
    }
}


void ProtocolClient::recv_match_id(uint* match_id) {
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        throw LostConnection();
    }
    if (was_closed) {
        throw LostConnection();
    }
    match_id[0] = ntohl(match_id[0]);
}

void ProtocolClient::recv_number_of_players(uint8_t* number_of_players) {
    socket.recvall(number_of_players, 1, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
}


std::map<uint, std::string> ProtocolClient::recv_list() {
    uint8_t num_of_matches[1];
    socket.recvall(num_of_matches, 1, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
    std::map<uint, std::string> matches_availables;
    for (int i = 0; i < num_of_matches[0]; i++) {
        uint match_id[1];
        socket.recvall(match_id, 4, &was_closed);
        if (was_closed) {
            throw LostConnection();
        }
        match_id[0] = ntohl(match_id[0]);
        uint8_t map_name_size[1];
        socket.recvall(map_name_size, 1, &was_closed);
        if (was_closed) {
            throw LostConnection();
        }
        std::vector<char> map_name(map_name_size[0]);
        socket.recvall(map_name.data(), map_name_size[0], &was_closed);
        if (was_closed) {
            throw LostConnection();
        }
        std::string map_name_str(map_name.begin(), map_name.end());
        matches_availables[match_id[0]] = map_name_str;
    }
    return matches_availables;
}

std::vector<std::string> ProtocolClient::recv_map_names() {
    uint16_t num_of_maps[1];
    socket.recvall(num_of_maps, 2, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
    num_of_maps[0] = ntohs(num_of_maps[0]);
    std::vector<std::string> map_names;
    for (int i = 0; i < num_of_maps[0]; i++) {
        uint16_t len[1];
        socket.recvall(len, 2, &was_closed);
        if (was_closed) {
            throw LostConnection();
        }
        len[0] = ntohs(len[0]);
        std::vector<char> map_name(len[0]);  // <char>??
        socket.recvall(map_name.data(), len[0], &was_closed);
        if (was_closed) {
            throw LostConnection();
        }
        std::string map_name_str(map_name.begin(), map_name.end());
        map_names.push_back(map_name_str);
    }
    return map_names;
}

uint8_t ProtocolClient::recv_number_of_players() {
    uint8_t number_of_players[1];
    socket.recvall(number_of_players, 1, &was_closed);
    if (was_closed) {
        throw LostConnection();
    }
    return number_of_players[0];
}
