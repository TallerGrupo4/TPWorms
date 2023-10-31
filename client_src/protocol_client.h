#include "../common_src/protocol.h"
#include "../common_src/socket.h"
#include "../common_src/constants.h"

#include "parser_client.h"

#ifndef PROTOCOLO_H
#define PROTOCOLO_H

class ProtocolClient: public Protocol {

private:
    int recv_match_id(uint* match_id);

public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    int recv(Command& command) override;

    int send(const Command& command) override;

    int send_create_join(Command& command);
};

#endif  // PROTOCOLO_H
