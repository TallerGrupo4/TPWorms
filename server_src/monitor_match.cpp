#include "monitor_match.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


MonitorMatch::MonitorMatch() {}

void MonitorMatch::add(const std::shared_ptr<Queue<Command>> queue) {
    std::unique_lock<std::mutex> lock(m);
    queues.push_back(queue);
}

void MonitorMatch::remove(const std::shared_ptr<Queue<Command>> queue) {
    std::unique_lock<std::mutex> lock(m);
    for (auto it = queues.begin(); it != queues.end(); ++it) {
        if (*it == queue) {
            queues.erase(it);
            break;
        }
    }
}

// cppcheck-suppress passedByValue
void MonitorMatch::push(const Command command) {
    std::unique_lock<std::mutex> lock(m);
    try {
        for (auto& queue: queues) {
            queue->push(command);
        }
    } catch (const ClosedQueue& err) {
        // It is an expected error
    } catch (...) {
        std::cerr << "Error in MonitorMatch::push: Unknown exception" << std::endl;
    }
}

bool MonitorMatch::is_full() {
    std::unique_lock<std::mutex> lock(m);
    return queues.size() == MAX_PLAYERS;
}

uint8_t MonitorMatch::get_players() {
    std::unique_lock<std::mutex> lock(m);
    return queues.size();
}

uint8_t MonitorMatch::get_player_index(const std::shared_ptr<Queue<Command>> queue) {
    std::unique_lock<std::mutex> lock(m);
    for (uint8_t index = 0; index < queues.size(); ++index) {
        if (queues[index] == queue) {
            return index;
        }
    }
    throw PlayerNotFound();
}

MonitorMatch::~MonitorMatch() {}
