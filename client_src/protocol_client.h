#include "../common_src/protocol.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#include "parser_client.h"

#ifndef PROTOCOLO_H
#define PROTOCOLO_H

class ProtocolClient: public Protocol {

private:
    int recv_match_id(uint* match_id);

public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    // Lobby
    int recv_command(Command& command) override;
    int send_command(Command& command) override;

    // Match
    int recv_snapshot(Snapshot& snapshot) override;
    int send_action(Action& action) override;
};

#endif  // PROTOCOLO_H
