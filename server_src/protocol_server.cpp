#include "protocol_server.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

ProtocolServer::ProtocolServer(Socket& socket, ParserServer& parser): socket(socket), parser(parser)/*Protocol(socket, parser)*/ {}

// ------------------------------ PUBLIC METHODS ------------------------------

int ProtocolServer::send_command(Command& command) {
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char code[1] = {command.code};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    switch (command.code) {
        case CASE_JOIN: {
            if (send_match_id(command) < 0) {
                return SOCKET_FAILED;
            }
            uint8_t number_of_players[1] = {command.number_of_players};
            if (socket.sendall(number_of_players, 1, &was_closed) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        case CASE_CREATE: {
            if (send_match_id(command) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        case CASE_MATCH_NOT_FOUND: {
            if (send_match_id(command) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            if (send_match_id(command) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        case CASE_MATCH_FULL: {
            if (send_match_id(command) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        default:
            break;
    }
    return 1;
}

int ProtocolServer::recv_command(Command& command) {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    switch (code[0]) {
        case CASE_CREATE: {
            return recv_create(command, code);
        }
        case CASE_JOIN: {
            return recv_join(command, code);
        }
        default:
            // Handle error
            break;
    }
    return -1;
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
        char type[1] = {platform.type};
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

int ProtocolServer::send_worms(std::vector<WormSnapshot>& worms) {
    return 1;
}

int ProtocolServer::recv_create(Command& command, const char* code) {
    uint match_id[1];
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    match_id[0] = ntohl(match_id[0]);
    parser.parse_receiving_command_create(command, code, match_id);
    return 0;
}

int ProtocolServer::recv_join(Command& command, const char* code) {
    uint match_id[1];
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    match_id[0] = ntohl(match_id[0]);
    parser.parse_receiving_command_join(command, code, match_id);
    return 0;
}

int ProtocolServer::send_match_id(const Command& command) {
    uint match_id[1] = {command.match_id};
    match_id[0] = htonl(match_id[0]);
    if (socket.sendall(match_id, 4, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    return 0;
}
