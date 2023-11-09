#include "protocol_client.h"
#include "../common_src/liberror.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <sys/types.h>

ProtocolClient::ProtocolClient(Socket& socket, ParserClient& parser): socket(socket), parser(parser) /*Protocol(socket, parser)*/ {}

int ProtocolClient::send_command(Command& command) {
    char code[1] = {command.code};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    uint len[1] = {htonl(command.match_id)};
    if (socket.sendall(len, 4, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    return 1;
}

int ProtocolClient::recv_command(Command& command) {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    command.code = code[0];
    switch (code[0]) {
        case CASE_JOIN: {
            uint match_id[1];
            recv_match_id(match_id);
            uint8_t number_of_players[1];
            ret = socket.recvall(number_of_players, 1, &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            parser.parse_receiving_command_join(command, code, match_id, number_of_players);
            break;
        }
        case CASE_CREATE: {
            uint match_id[1];
            recv_match_id(match_id);
            parser.parse_receiving_command_create(command, code, match_id);
            break;
        }
        case CASE_MATCH_FULL: {
            uint match_id[1];
            recv_match_id(match_id);
            parser.parse_receiving_command_full(command, code, match_id);
            break;
        }
        case CASE_EXIT_SERVER: {
            uint8_t number_of_players[1];
            ret = socket.recvall(number_of_players, 1, &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            uint8_t player_index[1];
            ret = socket.recvall(player_index, 1, &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            parser.parse_receiving_command_exit(command, code, number_of_players, player_index);
        }
        case CASE_MATCH_NOT_FOUND: {
            uint match_id[1];
            recv_match_id(match_id);
            parser.parse_receiving_command_not_found(command, code, match_id);
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            uint match_id[1];
            recv_match_id(match_id);
            parser.parse_receiving_command_already_exists(command, code, match_id);
            break;
        }
        default:
            break;
    }
    if (was_closed) {
        return WAS_CLOSED;
    }
    return 1;
}



int ProtocolClient::send_action(Action& action) {
    return action.send(socket, was_closed);
}

// int ProtocolClient::recv_snapshot(Snapshot& snapshot) {
Snapshot ProtocolClient::recv_snapshot() {
    char code[1];
    socket.recvall(code, 1, &was_closed);
    if (code[0] == MAP) return recv_platforms();
    else if (code[0] == WORMS) return recv_worms();
    return Snapshot();
}


// int ProtocolClient::recv_platforms(Snapshot& snapshot) {
Snapshot ProtocolClient::recv_platforms() {
    Snapshot snapshot;
    uint16_t num_of_plats[1];
    socket.recvall(num_of_plats, 2, &was_closed);
    // if (was_closed) throw WasClosed;
    num_of_plats[0] = ntohs(num_of_plats[0]);
    for (int i = 0; i < num_of_plats[0]; i++) {
        char type[1];
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

// int ProtocolClient::recv_worms(Snapshot& snapshot) {
Snapshot ProtocolClient::recv_worms() {
    return Snapshot();
}


int ProtocolClient::recv_match_id(uint* match_id) {
    int ret = socket.recvall(match_id, 4, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        return WAS_CLOSED;
    }
    match_id[0] = ntohl(match_id[0]);
    return 0;
}
