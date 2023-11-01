#include <memory>

#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "parser_server.h"
#include "protocol_server.h"

#ifndef SERVER_CLIENT_SENDER_H
#define SERVER_CLIENT_SENDER_H

class ServerClientSender: public Thread {
private:
    Socket& socket;
    std::shared_ptr<Queue<Command>> queue;
    ParserServer parser;
    ProtocolServer& protocol;

public:
    explicit ServerClientSender(Socket& skt, std::shared_ptr<Queue<Command>> queue,
                                ProtocolServer& protocol);

    virtual void run() override;

    ~ServerClientSender();
};

#endif  // SERVER_CLIENT_SENDER_H
