#include <atomic>
#include <memory>

#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"
// #include "../common_src/game_command.h"
#include "game_src/game_command.h"

#include "match.h"
#include "monitor_matches.h"
#include "parser_server.h"
#include "protocol_server.h"
#include "user_sender.h"

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

class User: public Thread {
private:
    Socket socket;
    // std::shared_ptr<Queue<GameCommand*>> queue_match = NULL;
    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> queue_match = NULL;
    ParserServer parser;
    ProtocolServer protocol;
    std::unique_ptr<UserSender> sender;
    MonitorMatches& monitor_matches;
    bool _is_dead = false;
    uint match_id = 0;
    bool interpretate_command_in_lobby(Command& command);
    void interpretate_command_in_match(GameCommand& game_command);
    void handle_lobby();
    void handle_match();

public:
    explicit User(Socket&& skt, MonitorMatches& _monitor_matches);

    virtual void run() override;

    bool is_dead();

    void stop();

    ~User();
};

#endif  // SERVER_CLIENT_H
