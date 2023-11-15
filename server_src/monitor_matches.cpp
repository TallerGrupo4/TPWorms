#include "monitor_matches.h"

#include <iostream>
#include <memory>

#include "../common_src/constants.h"
#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

MonitorMatches::MonitorMatches() {}

std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::create_match(
        std::shared_ptr<Queue<Snapshot>> queue, uint match_id, uint8_t& worm_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();
    matches[match_id] = std::make_unique<Match>("map1");
    worm_id = matches[match_id]->add_player(queue);
    return matches[match_id]->get_queue();
}

void MonitorMatches::stop() {
    std::unique_lock<std::mutex> lock(m);
    for (auto& match: matches) {
        match.second->stop();
        match.second->join();
    }
}

void MonitorMatches::start_match(uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    if (matches[match_id]->has_started())
        throw MatchAlreadyStarted();
    matches[match_id]->start_match();
}

std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::join_match(
        std::shared_ptr<Queue<Snapshot>> queue, uint match_id, uint8_t& worm_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    worm_id = matches[match_id]->add_player(queue);
    return matches[match_id]->get_queue();
}

std::map<uint, std::string> MonitorMatches::list_matches() {
    std::unique_lock<std::mutex> lock(m);
    std::map<uint, std::string> matches_availables;
    for (auto& match: matches) {
        if (!match.second->has_started())
            matches_availables[match.first] = match.second->get_map_name();
    }
    return matches_availables;
}

MonitorMatches::~MonitorMatches() {}
