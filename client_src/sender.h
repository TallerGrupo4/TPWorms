#include <atomic>
#include <memory>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "parser_client.h"
#include "protocol_client.h"

class ClientSender: public Thread {
private:
    Socket& socket;
    std::shared_ptr<Queue<Command>> queue_lobby;
    std::shared_ptr<Queue<Command>> queue_match;
    std::atomic<bool>& in_match;
    ParserClient parser;
    ProtocolClient protocol;
    std::atomic<bool>& is_dead;
    void handle_lobby();
    void handle_match();

public:
    explicit ClientSender(Socket& skt, std::shared_ptr<Queue<Command>> _queue_lobby,
                          std::shared_ptr<Queue<Command>> _queue_match,
                          std::atomic<bool>& _in_match, std::atomic<bool>& _is_dead);

    void run() override;

    bool is_connected() { return protocol.is_connected(); }

    ~ClientSender();
};
