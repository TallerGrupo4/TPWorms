#include <atomic>
#include <memory>

#include "../common_src/common_monitor_match.h"
#include "../common_src/common_monitor_matches.h"
#include "../common_src/common_socket.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "server_parser_server.h"
#include "server_protocol_server.h"
#include "server_server_client_sender.h"

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

class ServerClient: public Thread {
private:
    Socket socket;
    std::shared_ptr<Queue<Command>> queue;
    ParserServer parser;
    ProtocolServer protocol;
    std::unique_ptr<ServerClientSender> sender;
    MonitorMatches& monitor_matches;
    std::shared_ptr<MonitorMatch> monitor_match = NULL;
    bool _is_dead = false;
    void interpretate_command(Command& command);

public:
    explicit ServerClient(Socket&& skt, MonitorMatches& _monitor_matches);

    virtual void run() override;

    bool is_dead();

    void stop();

    ~ServerClient();
};

#endif  // SERVER_CLIENT_H
