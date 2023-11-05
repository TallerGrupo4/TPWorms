#include <memory>
#include <atomic>

#include "../common_src/socket.h"
#include "../common_src/constants.h"
#include "../common_src/queue.h"

#include "receiver.h"
#include "sender.h"
#include "parser_client.h"

class Client {
private:
    Socket socket;
    std::atomic<bool> is_dead = false;
    std::atomic<bool> in_match = false;
    std::shared_ptr<Queue<Command>> queue_sender_lobby;
    std::shared_ptr<Queue<Command>> queue_sender_match;
    std::shared_ptr<Queue<Command>> queue_receiver_lobby;
    std::shared_ptr<Queue<Command>> queue_receiver_match;
    std::unique_ptr<ClientSender> client_sender;
    std::unique_ptr<ClientReceiver> client_receiver;
    ParserClient parser;
    void stop();
    void handle_command_not_in_match(Command& command);
    void handle_command_in_match(Command& command);
    void get_command(Command& command);
    void print_command(const Command& command);

public:
    explicit Client(const char* hostname, const char* servername);

    int start();

    ~Client();
};
