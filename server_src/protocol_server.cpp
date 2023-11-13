#include "protocol_server.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

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
            send_map_name(command.get_map_name());
            break;
        }
        case CASE_CREATE: {
            send_match_id(command.get_match_id());
            send_map_name(command.get_map_name());
            break;
        }
        case CASE_MATCH_NOT_FOUND: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_LIST: {
            send_list(command.get_matches_availables());
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            send_match_id(command.get_match_id());
            break;
        }
        case CASE_MATCH_FULL: {
            send_match_id(command.get_match_id());
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
        case CASE_LIST:
            return recv_list(code);
        default:
            // Handle error
            break;
    }
    // Handle error
    return Command(DEFAULT, DEFAULT);
}

int ProtocolServer::send_snapshot(Snapshot& snapshot) {
    if (snapshot.worms.empty()) {
        // Move this into a function
        char is_map[1] = {MAP};
        if (socket.sendall(is_map, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        if (was_closed) {
            throw LibError(errno, "Socket was closed");
        }
        if (send_platforms(snapshot.platforms) < 0) {
            return SOCKET_FAILED;
        }
    } else {
        // Move this into a function
        char is_worms[1] = {WORMS};
        if (socket.sendall(is_worms, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        if (was_closed) {
            throw LibError(errno, "Socket was closed");
        }
        if (send_worms(snapshot.worms) < 0) {
            return SOCKET_FAILED;
        }
    }
    return 1;
}

std::shared_ptr<GameCommand> ProtocolServer::recv_game_command() {
    char code[1];
    socket.recvall(code, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    switch (code[0]) {
        case MOV: {
            return recv_mov();
        }
        case START: {
            return recv_start();
        }
        default:
            // Dummy GameCommand, it does nothing (or maybe it says that the client has disconnected?).
            return std::make_shared<GameCommand>();
    }
}


// ------------------------------ PRIVATE METHODS ------------------------------

std::shared_ptr<GameCommand> ProtocolServer::recv_start() {
    return std::make_shared<StartCommand>();
}

std::shared_ptr<GameCommand> ProtocolServer::recv_mov() {
    char id_worm[1];
    int ret = socket.recvall(id_worm, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char movement_x[1];
    ret = socket.recvall(movement_x, 1, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    // parser.parse_receiving_game_command(game_command, MOV, id_worm, movement_x);
    return std::make_shared<MoveCommand>(id_worm[0], movement_x[0]);
}

int ProtocolServer::send_platforms(std::vector<PlatformSnapshot>& platforms) {
    uint16_t num_of_plats[1] = {htons(platforms.size())};
    if (socket.sendall(num_of_plats, 2, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    for (auto& platform : platforms) {
        // Check if 'type' is really a char or if it's an int
        BeamType type[1] = {platform.type};
        if (socket.sendall(type, 1, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_x[1] = {static_cast<int>(platform.pos_x * MULTIPLIER)};
        pos_x[0] = htonl(pos_x[0]);
        if (socket.sendall(pos_x, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int pos_y[1] = {static_cast<int>(platform.pos_y * MULTIPLIER)};
        pos_y[0] = htonl(pos_y[0]);
        if (socket.sendall(pos_y, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
        int angle[1] = {static_cast<int>(platform.angle * MULTIPLIER)};
        angle[0] = htonl(angle[0]);
        if (socket.sendall(angle, 4, &was_closed) < 0) {
            return SOCKET_FAILED;
        }
    }
    return 1;
}

/*
    char id;
    float pos_x;
    float pos_y;
    float angle;
    int max_health;
    int health;
    int direction;
    int weapon;
    int state;
*/
/*
send_worm, list_matches, id_of_my_worm, complete the Command class
*/
int ProtocolServer::send_worms(std::vector<WormSnapshot>& worms) {
    
    return 1;
}

const Command ProtocolServer::recv_create(const char* code) {
    return recv_match_id(code);
}

const Command ProtocolServer::recv_join(const char* code) {
    return recv_match_id(code);
}

const Command ProtocolServer::recv_match_id(const char* code) {
    uint match_id[1];
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        // throw
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    match_id[0] = ntohl(match_id[0]);
    return Command(code[0], match_id[0]);
}

const Command ProtocolServer::recv_list(const char* code) {
    return Command(code[0], DEFAULT);
}

void ProtocolServer::send_match_id(const uint _match_id) {
    uint match_id[1] = {_match_id};
    match_id[0] = htonl(match_id[0]);
    socket.sendall(match_id, 4, &was_closed);
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
