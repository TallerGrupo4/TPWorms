#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../common_src/constants.h"
#include "../common_src/snapshot.h"
#include "../common_src/game_command.h"
// #include "../server_src/game_src/gameCommand.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"

#include "parser_client.h"
#include "receiver.h"
#include "sender.h"

class Client {
private:
    Socket socket;
    std::atomic<bool> is_dead = false;
    std::atomic<bool> in_match = false;
    std::shared_ptr<Queue<Command>> queue_sender_lobby;
    std::shared_ptr<Queue<GameCommand>> queue_sender_match;
    std::shared_ptr<Queue<Command>> queue_receiver_lobby;
    std::shared_ptr<Queue<Snapshot>> queue_receiver_match;
    std::unique_ptr<ClientSender> client_sender;
    std::unique_ptr<ClientReceiver> client_receiver;
    ParserClient parser;
    void stop();
    void get_action(Command& command, GameCommand& game_command);
    void print_snapshot(const Snapshot& snapshot);
    void print_command(const Command& command);
    bool is_connected();

public:
    explicit Client(const char* hostname, const char* servername);

    int start();

    Command pop_command();

    Snapshot pop_snapshot();

    void push_command(Command command);

    void push_game_command(GameCommand game_command);

    void exit();

    ~Client();
};
#endif  // CLIENT_H
