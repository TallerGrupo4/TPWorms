#include "../common_src/constants.h"
#include "../common_src/snapshot.h"
#include "action.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#include "parser_client.h"

#ifndef PROTOCOLO_H
#define PROTOCOLO_H

class ProtocolClient {

private:
    Socket& socket;
    bool was_closed = false;
    ParserClient& parser;
    
    int recv_match_id(uint* match_id);
    Snapshot recv_platforms();
    Snapshot recv_worms();

public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    // Lobby
    int recv_command(Command& command);
    int send_command(Command& command);

    // Match
    Snapshot recv_snapshot();
    int send_action(Action& action);
    bool is_connected() { return !was_closed;}
    
    bool operator==(const ProtocolClient& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolClient& other) const { return !(*this == other); }
};

#endif  // PROTOCOLO_H