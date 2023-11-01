#include "protocol_server.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>

#include "../common_src/liberror.h"
#include "../common_src/constants.h"

ProtocolServer::ProtocolServer(Socket& socket, ParserServer& parser): Protocol(socket, parser) {}


int ProtocolServer::send(const Command& command) {
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    char code[1] = {command.code};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    switch (command.code) {
        case CASE_EXIT_SERVER: {
            uint8_t number_of_players[1] = {command.number_of_players};
            if (socket.sendall(number_of_players, 1, &was_closed) < 0) {
                return SOCKET_FAILED;
            }
            uint8_t player_index[1] = {command.player_index};
            if (socket.sendall(player_index, 1, &was_closed) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
        case CASE_CHAT: {
            uint16_t len[1] = {htons(command.msg.size())};
            if (socket.sendall(len, 2, &was_closed) < 0) {
                return SOCKET_FAILED;
            }
            if (socket.sendall(command.msg.c_str(), command.msg.length(), &was_closed) < 0) {
                return SOCKET_FAILED;
            }
            break;
        }
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

int ProtocolServer::recv(Command& command) {
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
        case CASE_CHAT: {
            return recv_chat(command, code);
        }
        default:
            // Handle error
            break;
    }
    return -1;
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

int ProtocolServer::recv_chat(Command& command, const char* code) {
    uint16_t len[1];
    int ret = socket.recvall(len, 2, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    len[0] = ntohs(len[0]);
    std::vector<char> msg(len[0]);
    ret = socket.recvall(msg.data(), len[0], &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    if (was_closed) {
        throw LibError(errno, "Socket was closed");
    }
    parser.parse_receiving_command_chat(command, code, msg);
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
