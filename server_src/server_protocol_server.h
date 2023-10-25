#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "../common_src/constants.h"

#include "server_parser_server.h"

#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

class ProtocolServer: public Protocol {

private:
    int send_match_id(const Command& command);

public:
    explicit ProtocolServer(Socket& socket, ParserServer& parser);

    int recv(Command& command) override;

    int send(const Command& command) override;

    int recv_create(Command& command, const char* code);

    int recv_join(Command& command, const char* code);

    int recv_chat(Command& command, const char* code);
};

#endif  // PROTOCOL_SERVER_H
