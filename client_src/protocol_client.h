#include "../common_src/constants.h"
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

    int recv_lobby(Command& command) override;

    int recv_match(Command& command) override;

    int send_lobby(const Command& command) override;

    int send_match(const Command& command) override;
};

#endif  // PROTOCOLO_H
