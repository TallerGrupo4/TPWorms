#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../common_src/command.h"
#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshot.h"
#include "../common_src/socket.h"

#include "actions.h"
#include "parser_client.h"
#include "protocol_client.h"
#include "receiver.h"
#include "sender.h"

class Client {
private:
    Socket socket;
    std::atomic<bool> is_dead = false;
    std::atomic<bool> in_match = false;
    std::shared_ptr<Queue<Command>> queue_sender_lobby;
    std::shared_ptr<Queue<std::shared_ptr<Action>>> queue_sender_match;
    std::shared_ptr<Queue<Command>> queue_receiver_lobby;
    std::shared_ptr<Queue<Snapshot>> queue_receiver_match;
    std::unique_ptr<ClientSender> client_sender;
    std::unique_ptr<ClientReceiver> client_receiver;
    ParserClient parser;
    ProtocolClient protocol;
    void stop();
    void print_snapshot(const Snapshot& snapshot);
    void print_command(const Command& command);

public:
    explicit Client(const char* hostname, const char* servername);

    void start();

    Command recv_lobby_command();

    bool recv_snapshot(Snapshot& snapshot);

    Snapshot recv_map();

    void send_lobby_command(const Command& command);

    void send_action(std::shared_ptr<Action>);

    void exit();

    bool is_connected();

    ~Client();
};
#endif  // CLIENT_H
