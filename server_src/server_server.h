#include <atomic>
#include <memory>
#include <vector>

#include "../common_src/common_monitor_matches.h"
#include "../common_src/common_socket.h"
#include "../common_src/thread.h"

#include "server_server_client.h"

#ifndef SERVER_H
#define SERVER_H

class Server: public Thread {
private:
    Socket socket;
    MonitorMatches monitor_matches;
    bool is_dead = false;
    std::vector<std::unique_ptr<ServerClient>> clients;
    /*
     * We store the clients in a Vector using shared pointers to avoid memory leaks ("RAII").
     * (Perhaps it is a little bit overkill, but it is a good practice)
     */
    void free_dead_clients();
    void kill_clients();

public:
    explicit Server(const char* port);

    void run() override;

    void stop();

    ~Server();
};

#endif  // SERVER_H
