#include <memory>

#include "../common_src/common_socket.h"
#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "client_parser_client.h"
#include "client_protocol_client.h"

class ClientReceiver: public Thread {
private:
    Socket& socket;
    std::shared_ptr<Queue<Command>> queue;
    bool& in_match;
    bool _is_dead = false;
    ParserClient parser;
    ProtocolClient protocol;

public:
    explicit ClientReceiver(Socket& skt, std::shared_ptr<Queue<Command>> queue, bool& in_match);

    void run() override;

    bool is_connected() { return protocol.is_connected(); }

    ~ClientReceiver();
};
