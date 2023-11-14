#include <memory>
// #include "../common_src/protocol.h"
#include "game_src/game_command.h"
#include "../common_src/snapshot.h"
#include "../common_src/constants.h"

#include "parser_server.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

class ProtocolServer/*: public Protocol*/ {

private:
    Socket& socket;
    bool was_closed = false;
    ParserServer& parser;

private:
    int send_match_id(const Command& command);
    void send_worm_id(const uint8_t& worm_id);
    int recv_create(Command& command, const char* code);
    int recv_join(Command& command, const char* code);
    int send_platforms(std::vector<PlatformSnapshot>& platforms);
    int send_worms(std::vector<WormSnapshot>& worms);
    std::shared_ptr<GameCommand> recv_mov();
    std::shared_ptr<GameCommand> recv_start();

public:
    explicit ProtocolServer(Socket& socket, ParserServer& parser);

    // Lobby
    int send_command(Command& command) /*override*/;
    int recv_command(Command& command) /*override*/;

    // Match
    int send_snapshot(Snapshot& snapshot) /*override*/;
    // int recv_game_command(std::shared_ptr<GameCommand> game_command) /*override*/;
    std::shared_ptr<GameCommand> recv_game_command();
    bool is_connected() { return !was_closed;}


    bool operator==(const ProtocolServer& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolServer& other) const { return !(*this == other); }
};

#endif  // PROTOCOL_SERVER_H
