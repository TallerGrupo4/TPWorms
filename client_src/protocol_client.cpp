#include "protocol_client.h"
#include "../common_src/liberror.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <sys/types.h>

ProtocolClient::ProtocolClient(Socket& socket, ParserClient& parser): socket(socket), parser(parser) {}

void ProtocolClient::send_command(const Command& command) {
    char code[1] = {command.get_code()};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        // throw error...
    }
    if (code[0] == CASE_JOIN || code[0] == CASE_CREATE) {
        // Send match_id
        uint len[1] = {htonl(command.get_match_id())};
        if (socket.sendall(len, 4, &was_closed) < 0) {
            // throw error...
        }
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
            std::string map_name = recv_map_name();
            return Command(code[0], match_id[0], map_name);
        }
        case CASE_CREATE: {
            uint match_id[1];
            recv_match_id(match_id);
            std::string map_name = recv_map_name();
            return Command(code[0], match_id[0], map_name);
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
        default:
            break;
    }
    if (was_closed) {
        // Throw
    }
    // Throw error
    return Command(DEFAULT, DEFAULT);
}



void ProtocolClient::send_action(Action& action) {
    action.send(socket, was_closed);
}

Snapshot ProtocolClient::recv_snapshot() {
    char code[1];
    socket.recvall(code, 1, &was_closed);
    if (code[0] == MAP) return recv_platforms();
    else if (code[0] == WORMS) return recv_worms();
    return Snapshot();
}


Snapshot ProtocolClient::recv_platforms() {
    Snapshot snapshot;
    uint16_t num_of_plats[1];
    socket.recvall(num_of_plats, 2, &was_closed);
    // if (was_closed) throw WasClosed;
    num_of_plats[0] = ntohs(num_of_plats[0]);
    for (int i = 0; i < num_of_plats[0]; i++) {
        BeamType type[1];
        int pos_x[1];
        int pos_y[1];
        int angle[1];
        socket.recvall(type, 1, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_x, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(pos_y, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        socket.recvall(angle, 4, &was_closed);
    // if (was_closed) throw WasClosed;
        pos_x[0] = ntohl(pos_x[0]);
        pos_y[0] = ntohl(pos_y[0]);
        angle[0] = ntohl(angle[0]);
        // The pos_x and pos_y are multiplied by 1000 to avoid sending floats
        // The client must know that it probably has to divide by 1000
        // (The platforms have integers instead of floats from now on in the client)
        PlatformSnapshot platform(type[0], pos_x[0], pos_y[0], angle[0]);
        snapshot.platforms.push_back(platform);
    }
    return snapshot;
}

Snapshot ProtocolClient::recv_worms() {
    return Snapshot();
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
