#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <atomic>
#include <memory>

#include "../common_src/constants.h"
#include "../common_src/command.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "action.h"
#include "parser_client.h"
#include "protocol_client.h"

class ClientSender: public Thread {
private:
    Socket& socket;
    std::shared_ptr<Queue<Command>> queue_lobby;
    // std::shared_ptr<Queue<std::shared_ptr<Action>>> queue_match;
    std::shared_ptr<Queue<Action>> queue_match;
    std::atomic<bool>& in_match;
    ParserClient parser;
    ProtocolClient protocol;
    std::atomic<bool>& is_dead;

public:
    explicit ClientSender(Socket& skt, std::shared_ptr<Queue<Command>> _queue_lobby,
                          std::shared_ptr<Queue<Action>> _queue_match,
                          std::atomic<bool>& _in_match, std::atomic<bool>& _is_dead);

    void run() override;

    bool is_connected() { return protocol.is_connected(); }

    ~ClientSender();
};
#endif // CLIENT_SENDER_H
