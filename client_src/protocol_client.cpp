#include "protocol_client.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>

ProtocolClient::ProtocolClient(Socket& socket, ParserClient& parser): Protocol(socket, parser) {}

int ProtocolClient::recv_lobby(Command& command) {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    command.code = code[0];
    switch (code[0]) {
        case CASE_CHAT: {
            uint16_t len[1];
            ret = socket.recvall(len, 2, &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            len[0] = ntohs(len[0]);
            std::vector<char> msg(len[0]);
            ret = socket.recvall(msg.data(), len[0], &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            parser.parse_receiving_command_chat(command, code, msg);
            break;
        }
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

int ProtocolClient::recv_match(Command& command) {
    char code[1];
    int ret = socket.recvall(code, 1, &was_closed);
    if (ret < 0) {
        return SOCKET_FAILED;
    }
    command.code = code[0];
    switch (code[0]) {
        case CASE_CHAT: {
            uint16_t len[1];
            ret = socket.recvall(len, 2, &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            len[0] = ntohs(len[0]);
            std::vector<char> msg(len[0]);
            ret = socket.recvall(msg.data(), len[0], &was_closed);
            if (ret < 0) {
                return SOCKET_FAILED;
            }
            if (was_closed) {
                return WAS_CLOSED;
            }
            parser.parse_receiving_command_chat(command, code, msg);
            break;
        }
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

int ProtocolClient::send_match(const Command& command) {
    char code[1] = {command.code};
    if (socket.sendall(code, 1, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    uint16_t len[1] = {htons(command.msg.size())};
    if (socket.sendall(len, 2, &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    if (socket.sendall(command.msg.c_str(), command.msg.length(), &was_closed) < 0) {
        return SOCKET_FAILED;
    }
    return 1;
}

int ProtocolClient::send_lobby(const Command& command) {
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
