#include "constants.h"
#include "parser.h"
#include "socket.h"
#include "snapshot.h"
#include "game_command.h"
// #include "../server_src/game_src/gameCommand.h"

#ifdef TESTING
#include "dummy_socket.h"
#else
#include "socket.h"
#endif

#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {

protected:
    Socket& socket;
    bool was_closed = false;
    Parser& parser;

public:
    explicit Protocol(Socket& socket, Parser& parser);

    // Lobby
    virtual int recv_command(Command& command);
    virtual int send_command(Command& command);

    // Match
    virtual int recv_snapshot(Snapshot& snapshot);
    virtual int send_snapshot(Snapshot& snapshot);
    virtual int recv_game_command(GameCommand& game_command);
    virtual int send_game_command(GameCommand& game_command);

    virtual bool is_connected();

    bool operator==(const Protocol& other) const { return this->socket == other.socket; }
    bool operator!=(const Protocol& other) const { return !(*this == other); }

    ~Protocol();
};

#endif  // PROTOCOL_H
