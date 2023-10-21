#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "../common_src/constants.h"

#include "client_parser_client.h"

#ifndef PROTOCOL_CLIENT_H
#define PROTOCOL_CLIENT_H

class ProtocolClient: public Protocol {

private:
    int recv_match_id(uint* match_id);

public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    int recv(Command& command) override;

    int send(const Command& command) override;

    int send_create_join(Command& command);
};

#endif  // PROTOCOL_CLIENT_H
