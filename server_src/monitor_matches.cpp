#include "monitor_matches.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"

MonitorMatches::MonitorMatches() {
    matches[1] = std::make_shared<MonitorMatch>();
    
}

std::shared_ptr<MonitorMatch> MonitorMatches::create(const std::shared_ptr<Queue<Command>> queue,
                                                     uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();
    matches[match_id] = std::make_shared<MonitorMatch>();
    matches[match_id]->add(queue);
    return matches[match_id];
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
