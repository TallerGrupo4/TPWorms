#include "monitor_matches.h"

#include <iostream>

#include "custom_errors.h"
#include "liberror.h"
#include "constants.h"

MonitorMatches::MonitorMatches() {}

std::shared_ptr<MonitorMatch> MonitorMatches::create(const std::shared_ptr<Queue<Command>> queue,
                                                     uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();
    matches[match_id] = std::make_shared<MonitorMatch>();
    matches[match_id]->add(queue);
    matches[match_id]->start();
    return matches[match_id];
}

void MonitorMatches::stop() {
    std::unique_lock<std::mutex> lock(m);
    for (auto& match: matches) {
        std::cout << "Stopping match: " << match.first << std::endl;
        match.second->stop();
        match.second->join();
    }
}

std::shared_ptr<MonitorMatch> MonitorMatches::join(const std::shared_ptr<Queue<Command>> queue,
                                                   uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    if (matches[match_id]->is_full())
        throw MatchFull();
    matches[match_id]->add(queue);
    return matches[match_id];
}

MonitorMatches::~MonitorMatches() {}
