#include "common_parser.h"
#include "common_socket.h"

#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {

protected:
    Socket& socket;
    bool was_closed = false;
    Parser& parser;

public:
    explicit Protocol(Socket& socket, Parser& parser);

    virtual int recv(Command& command);

    virtual int send(const Command& command);

    virtual bool is_connected();

    ~Protocol();
};

#endif  // PROTOCOL_H
