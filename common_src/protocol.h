#include "parser.h"
#include "socket.h"
#include "constants.h"
#include "../tests/dummy_socket.h"
#include "parser.h"
#include "socket.h"

#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol {

protected:
// #ifdef DUMMY_SOCKET_H
//     DummySocket& socket;
// #else
    Socket& socket;
// #endif
    bool was_closed = false;
    Parser& parser;

public:
// #ifdef TESTING
//     explicit Protocol(DummySocket& socket, Parser& parser) {
//         socket = socket;
//         parser = parser;
//     };
// #else
    explicit Protocol(Socket& socket, Parser& parser);
// #endif
    virtual int recv(Command& command);

    virtual int send(const Command& command);

    virtual bool is_connected();

    ~Protocol();
};

#endif  // PROTOCOL_H
