#include "protocol_client.h"
#include "../common_src/liberror.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

#include <arpa/inet.h>
#include <sys/types.h>

ProtocolClient::ProtocolClient(Socket& socket, ParserClient& parser): socket(socket), parser(parser) {}

// ------------------------------ PUBLIC ------------------------------

void ProtocolClient::send_command(const Command& command) {
    char code[1] = {command.get_code()};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        // throw error...
    }
    if (code[0] == CASE_JOIN || code[0] == CASE_CREATE) {
        // In CASE_START and CASE_NUMBER_OF_PLAYERS the match_id should be sent as well
        // Send_match_id(command.get_match_id());
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
        // Throw
    }
    switch (code[0]) {
        case CASE_JOIN: {
            uint match_id[1];
            recv_match_id(match_id);
            uint8_t worm_id = recv_worm_id();
            std::vector<std::string> maps_available = recv_map_names();
            const uint8_t number_of_players = recv_number_of_players();
            Command command(code[0], match_id[0], maps_available, number_of_players, worm_id);
            // Command command(code[0], match_id[0], worm_id);
            return command;
        }
        case CASE_CREATE: {
            uint match_id[1];
            recv_match_id(match_id);
            uint8_t worm_id = recv_worm_id();
            std::vector<std::string> maps_available = recv_map_names();
            const uint8_t number_of_players = recv_number_of_players();
            Command command(code[0], match_id[0], maps_available, number_of_players, worm_id);
            // Command command(code[0], match_id[0], worm_id);
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
            return Command(code[0], match_id[0], {""},  number_of_players[0], DEFAULT);
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
        // Throw
    }
    // Throw error
    return Command(DEFAULT, DEFAULT);
}



void ProtocolClient::send_action(std::shared_ptr<Action> action) {
    action->send(socket, was_closed);
}

Snapshot ProtocolClient::recv_snapshot() {
    Snapshot snapshot;
    recv_dimensions(snapshot);
    recv_platforms(snapshot);
    recv_time_and_worm_turn(snapshot);
    recv_worms(snapshot);
    return snapshot;
}


// ---------------------------------- PRIVATE ----------------------------------

void ProtocolClient::send_match_id(const uint match_id) {
    uint match_id_to_send = htonl(match_id);
    if (socket.sendall(&match_id_to_send, 4, &was_closed) < 0) {
        // throw error...
    }
}

void ProtocolClient::send_map_name(const std::string map_name) {
    uint16_t len = htons(static_cast<uint16_t>(map_name.size()));
    if (socket.sendall(&len, 2, &was_closed) < 0) {
        // throw error...
    }
    if (socket.sendall(map_name.c_str(), map_name.size(), &was_closed) < 0) {
        // throw error...
    }
}

void ProtocolClient::recv_dimensions(Snapshot& snapshot) {
    int width[1];
    int height[1];
    int worm_width[1];
    int worm_height[1];
    socket.recvall(width, 4, &was_closed);
    socket.recvall(height, 4, &was_closed);
    socket.recvall(worm_width, 4, &was_closed);
    socket.recvall(worm_height, 4, &was_closed);
    width[0] = ntohl(width[0]);
    height[0] = ntohl(height[0]);
    worm_width[0] = ntohl(worm_width[0]);
    worm_height[0] = ntohl(worm_height[0]);
    // Move this to  a 'Parser'
    snapshot.map_dimensions.width = std::round((static_cast<float>(width[0] * PIX_PER_METER)) / MULTIPLIER);
    snapshot.map_dimensions.height = std::round((static_cast<float>(height[0] * PIX_PER_METER)) / MULTIPLIER);
    snapshot.map_dimensions.worm_width = std::round((static_cast<float>(worm_width[0] * PIX_PER_METER)) / MULTIPLIER);
    snapshot.map_dimensions.worm_height = std::round((static_cast<float>(worm_height[0] * PIX_PER_METER)) / MULTIPLIER);
}

void ProtocolClient::recv_platforms(Snapshot& snapshot) {
    uint16_t num_of_plats[1];
    socket.recvall(num_of_plats, 2, &was_closed);
    // if (was_closed) throw WasClosed;
    num_of_plats[0] = ntohs(num_of_plats[0]);
    for (int i = 0; i < num_of_plats[0]; i++) {
        BeamType type[1];
        int pos_x[1];
        int pos_y[1];
        int width[1];
        int height[1];
        socket.recvall(type, 1, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_x, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_y, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(width, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(height, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        width[0] = ntohl(width[0]);
        height[0] = ntohl(height[0]);
        pos_x[0] = std::round((static_cast<float>(pos_x[0] * PIX_PER_METER)) / MULTIPLIER);
        pos_y[0] = std::round((static_cast<float>(pos_y[0] * PIX_PER_METER)) / MULTIPLIER);
        width[0] = std::round((static_cast<float>(width[0] * PIX_PER_METER)) / MULTIPLIER);
        height[0] = std::round((static_cast<float>(height[0] * PIX_PER_METER)) / MULTIPLIER);
        
        // PARSER!!!!
        int degree = 0;
        if (get_degree_of_beam_type(type[0], degree)) {
            height[0] = calculate_beam_height(degree, height[0], width[0]);
            width[0] = calculate_beam_width(degree, height[0], width[0]);
        }
        
        PlatformSnapshot platform( (BeamType(type[0])), pos_x[0], pos_y[0], width[0], height[0]);
        snapshot.platforms.push_back(platform);
    }
}

void ProtocolClient::recv_time_and_worm_turn(Snapshot& snapshot) {
    int turn_time[1];
    int worm_turn[1];
    socket.recvall(turn_time, 4, &was_closed);
    // if (was_closed) throw WasClosed;
    socket.recvall(worm_turn, 4, &was_closed);
    // if (was_closed) throw WasClosed;
    turn_time[0] = ntohl(turn_time[0]);
    worm_turn[0] = ntohl(worm_turn[0]);
    snapshot.turn_time_and_worm_turn.turn_time = turn_time[0];
    snapshot.turn_time_and_worm_turn.worm_turn = worm_turn[0];
}

void ProtocolClient::recv_worms(Snapshot& snapshot) {
    uint16_t num_of_worms[1];
    socket.recvall(num_of_worms, 2, &was_closed);
    // if (was_closed) throw WasClosed;
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
        socket.recvall(id, 1, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_x, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_y, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(angle, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(max_health, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(health, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(direction, 1, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(weapon, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(state, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        pos_x[0] = std::round((static_cast<float>(pos_x[0] * PIX_PER_METER)) / MULTIPLIER);
        pos_y[0] = std::round((static_cast<float>(pos_y[0] * PIX_PER_METER)) / MULTIPLIER);
        angle[0] = ntohl(angle[0]);
        angle[0] = std::round(static_cast<float>(angle[0]) / MULTIPLIER);
        max_health[0] = ntohl(max_health[0]);
        health[0] = ntohl(health[0]);
        weapon[0] = ntohl(weapon[0]);
        state[0] = ntohl(state[0]);
        WormSnapshot worm(id[0], pos_x[0], pos_y[0], angle[0], max_health[0], health[0], direction[0], weapon[0], state[0]);
        snapshot.worms.push_back(worm);
    }
}


void ProtocolClient::recv_match_id(uint* match_id) {
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        // throw
    }
    if (was_closed) {
        // throw
    }
    match_id[0] = ntohl(match_id[0]);
}

void ProtocolClient::recv_number_of_players(uint8_t* number_of_players) {
    socket.recvall(number_of_players, 1, &was_closed);
    if (was_closed) {
        // throw
    }
}

std::string ProtocolClient::recv_map_name() {
    uint16_t len[1];
    socket.recvall(len, 2, &was_closed);
    if (was_closed) {
        // throw
    }
    len[0] = ntohs(len[0]);
    std::vector<char> map_name(len[0]);
    socket.recvall(map_name.data(), len[0], &was_closed);
    if (was_closed) {
        // throw
    }
    std::string map_name_str(map_name.begin(), map_name.end());
    return map_name_str;
}

std::map<uint, std::string> ProtocolClient::recv_list() {
    uint8_t num_of_matches[1];
    socket.recvall(num_of_matches, 1, &was_closed);
    if (was_closed) {
        // throw
    }
    std::map<uint, std::string> matches_availables;
    for (int i = 0; i < num_of_matches[0]; i++) {
        uint match_id[1];
        socket.recvall(match_id, 4, &was_closed);
        if (was_closed) {
            // throw
        }
        match_id[0] = ntohl(match_id[0]);
        uint8_t map_name_size[1];
        socket.recvall(map_name_size, 1, &was_closed);
        if (was_closed) {
            // throw
        }
        std::vector<char> map_name(map_name_size[0]);
        socket.recvall(map_name.data(), map_name_size[0], &was_closed);
        if (was_closed) {
            // throw
        }
        std::string map_name_str(map_name.begin(), map_name.end());
        matches_availables[match_id[0]] = map_name_str;
    }
    return matches_availables;
}

uint8_t ProtocolClient::recv_worm_id() {
    uint8_t worm_id[1];
    socket.recvall(worm_id, 1, &was_closed);
    if (was_closed) {
        // throw
    }
    return worm_id[0];
}

std::vector<std::string> ProtocolClient::recv_map_names() {
    uint16_t num_of_maps[1];
    socket.recvall(num_of_maps, 2, &was_closed);
    if (was_closed) {
        // throw
    }
    num_of_maps[0] = ntohs(num_of_maps[0]);
    std::vector<std::string> map_names;
    for (int i = 0; i < num_of_maps[0]; i++) {
        uint16_t len[1];
        socket.recvall(len, 2, &was_closed);
        if (was_closed) {
            // throw
        }
        len[0] = ntohs(len[0]);
        std::vector<char> map_name(len[0]);  // <char>?? 
        socket.recvall(map_name.data(), len[0], &was_closed);
        if (was_closed) {
            // throw
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
        // throw
    }
    return number_of_players[0];
}

