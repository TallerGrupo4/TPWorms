#include <atomic>
#include <memory>
#include <vector>

#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "monitor_matches.h"
#include "user.h"

#ifndef SERVER_H
#define SERVER_H

class Server: public Thread {
private:
    Socket socket;
    MonitorMatches monitor_matches;
    bool is_dead = false;
    std::vector<std::unique_ptr<User>> users;
    /*
     * We store the users in a Vector using shared pointers to avoid memory leaks ("RAII").
     * (Perhaps it is a little bit overkill, but it is a good practice)
     */
    void free_dead_users();
    void kill_users();

public:
    explicit Server(const char* port);

    void run() override;

    void stop();

    ~Server();
};

#endif  // SERVER_H
