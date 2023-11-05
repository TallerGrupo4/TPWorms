#include "monitor_match.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


MonitorMatch::MonitorMatch(): queue_match(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)) {}

void MonitorMatch::run() {
    uint8_t FPS = 1;
    try {
        while (true) {
            push();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
        }
    } catch (const ClosedQueue& err) {
        // It is an expected error
    } catch (...) {
        std::cerr << "Error in MonitorMatch::run: Unknown exception" << std::endl;
    }
}

// void MonitorMatch::push_join() {
//     std::unique_lock<std::mutex> lock(m);
//     Command command = INITIALIZE_COMMAND;
//     command.code = CASE_JOIN_MATCH;
//     command.number_of_players = get_players() + 1;
//     try {
//         queue_match->try_push(command);
//     } catch (const ClosedQueue& err) {
//         // It is an expected error
//     } catch (...) {
//         std::cerr << "Error in MonitorMatch::push_join: Unknown exception" << std::endl;
//     }
// }

void MonitorMatch::stop() {
    std::unique_lock<std::mutex> lock(m);
    try {
        queue_match->close();
    } catch (const ClosedQueue& err) {
        // It is an expected error
    } catch (...) {
        std::cerr << "Error in MonitorMatch::stop: Unknown exception" << std::endl;
    }
}

std::shared_ptr<Queue<Command>> MonitorMatch::get_queue() {
    std::unique_lock<std::mutex> lock(m);
    return queue_match;
}

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

void MonitorMatch::push() {
    std::unique_lock<std::mutex> lock(m);
    Command command = INITIALIZE_COMMAND;
    if (queue_match->try_pop(command)) {
        try {
            for (auto& queue: queues) {
                std::cout << "pushing command: " << +command.code << std::endl;
                queue->try_push(command);
            }
        } catch (const ClosedQueue& err) {
            // It is an expected error
        } catch (...) {
            std::cerr << "Error in MonitorMatch::push: Unknown exception" << std::endl;
        }
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
