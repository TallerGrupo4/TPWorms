#include <memory>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"
#include "../common_src/queue.h"
#include "../common_src/snapshot.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "parser_server.h"
#include "protocol_server.h"

#ifndef SERVER_CLIENT_SENDER_H
#define SERVER_CLIENT_SENDER_H

class UserSender: public Thread {
private:
    Socket& socket;
    std::shared_ptr<Queue<Snapshot>> queue;
    ParserServer parser;
    ProtocolServer& protocol;

public:
    explicit UserSender(Socket& skt, ProtocolServer& protocol);

    virtual void run() override;

    void stop();

    std::shared_ptr<Queue<Snapshot>> get_queue();

    ~UserSender();
};

#endif  // SERVER_CLIENT_SENDER_H
