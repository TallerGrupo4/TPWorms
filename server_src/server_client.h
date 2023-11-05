#include <atomic>
#include <memory>

#include "monitor_match.h"
#include "monitor_matches.h"
#include "../common_src/socket.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "parser_server.h"
#include "protocol_server.h"
#include "server_client_sender.h"

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

class ServerClient: public Thread {
private:
    Socket socket;
    std::shared_ptr<Queue<Command>> queue;
    std::shared_ptr<Queue<Command>> queue_match = NULL;
    ParserServer parser;
    ProtocolServer protocol;
    std::unique_ptr<ServerClientSender> sender;
    MonitorMatches& monitor_matches;
    std::shared_ptr<MonitorMatch> monitor_match = NULL;
    bool _is_dead = false;
    bool interpretate_command_in_lobby(Command& command);
    void interpretate_command_in_match(Command& command);
    void handle_lobby();
    void handle_match();

public:
    explicit ServerClient(Socket&& skt, MonitorMatches& _monitor_matches);

    virtual void run() override;

    bool is_dead();

    void stop();

    ~ServerClient();
};

#endif  // SERVER_CLIENT_H
