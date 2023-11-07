#include "../common_src/protocol.h"

#include "parser_server.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

class ProtocolServer: public Protocol {

private:
    int send_match_id(const Command& command);
    int recv_create(Command& command, const char* code);
    int recv_join(Command& command, const char* code);
    // int recv_chat(Command& command, const char* code);

public:
    explicit ProtocolServer(Socket& socket, ParserServer& parser);

    // Lobby
    int send_command(Command& command) override;
    int recv_command(Command& command) override;

    // Match
    int send_snapshot(Snapshot& snapshot) override;
    int recv_game_command(GameCommand& game_command) override;
};

#endif  // PROTOCOL_SERVER_H
