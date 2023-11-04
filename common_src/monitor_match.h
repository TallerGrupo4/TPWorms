#include <memory>
#include <vector>

#include "constants.h"
#include "queue.h"
#include "thread.h"


#ifndef MONITOR_MATCH_H
#define MONITOR_MATCH_H

class MonitorMatch: public Thread {
private:
    std::vector<std::shared_ptr<Queue<Command>>> queues;
    std::shared_ptr<Queue<Command>> queue_match;
    std::mutex m;

public:
    MonitorMatch();

    virtual void run() override;

    void stop();

    std::shared_ptr<Queue<Command>> get_queue();

    void add(const std::shared_ptr<Queue<Command>> queue);

    void remove(const std::shared_ptr<Queue<Command>> queue);

    void push();

    bool is_full();

    uint8_t get_players();

    uint8_t get_player_index(const std::shared_ptr<Queue<Command>> queue);

    // void push_join();

    ~MonitorMatch();
};

#endif  // MONITOR_MATCH_H
