#include "parser.h"
#include "socket.h"
#include "constants.h"
#include "parser.h"

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

    virtual int recv(Command& command);

    virtual int send(const Command& command);

    virtual bool is_connected();

    bool operator==(const Protocol& other) const { return this->socket == other.socket; };
    bool operator!=(const Protocol& other) const { return !(*this == other); };

    ~Protocol();
};

#endif  // PROTOCOL_H
