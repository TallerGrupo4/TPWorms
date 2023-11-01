#include <memory>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/queue.h"


#ifndef MONITOR_MATCH_H
#define MONITOR_MATCH_H

class MonitorMatch {
private:
    std::vector<std::shared_ptr<Queue<Command>>> queues;
    std::mutex m;

public:
    MonitorMatch();

    void add(const std::shared_ptr<Queue<Command>> queue);

    void remove(const std::shared_ptr<Queue<Command>> queue);

    // cppcheck-suppress passedByValue
    void push(const Command command);

    bool is_full();

    uint8_t get_players();

    uint8_t get_player_index(const std::shared_ptr<Queue<Command>> queue);

    ~MonitorMatch();
};

#endif  // MONITOR_MATCH_H
