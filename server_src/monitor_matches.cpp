#include "monitor_matches.h"

#include <algorithm>
#include <cstdint>

#include <sys/types.h>

#include "../common_src/constants.h"
#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

#include "map_reader.h"


MonitorMatches::MonitorMatches(std::vector<std::string> routes) {
    uint map_id = 1;
    try {
        for (auto& route: routes) {
            MapReader reader(route);
            Map map = reader.read_map();
            maps[map.name] = map;
        }
    } catch (...) {
        std::cerr << "Error reading map with id: " << map_id << std::endl;
        throw;
    }
}

std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::create_match(
        std::shared_ptr<Queue<Snapshot>> queue, uint match_id, uint8_t& number_of_players,
        std::vector<std::string>& map_names, uint8_t& army_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();

    std::cout << _YELLOW << "Creating match with id: " << _RESET << match_id << std::endl;
    matches[match_id] = std::make_unique<Match>();
    army_id = matches[match_id]->add_player(queue);
    number_of_players = matches[match_id]->get_number_of_players();
    std::transform(maps.begin(), maps.end(), std::back_inserter(map_names),
                   [](const auto& map) { return map.second.name; });
    kill_dead_matches();

    return matches[match_id]->get_queue();
}

std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::join_match(
        std::shared_ptr<Queue<Snapshot>> queue, uint match_id, uint8_t& number_of_players,
        std::vector<std::string>& map_names, uint8_t& army_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    army_id = matches[match_id]->add_player(queue);
    number_of_players = matches[match_id]->get_number_of_players();
    std::transform(maps.begin(), maps.end(), std::back_inserter(map_names),
                   [](const auto& map) { return map.second.name; });
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


void MonitorMatches::stop() {
    std::unique_lock<std::mutex> lock(m);
    kill_dead_matches();
    for (auto& match: matches) {
        match.second->stop();
        match.second->join();
    }
}

void MonitorMatches::start_match(uint match_id, std::string map_name) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    if (matches[match_id]->has_started())
        throw MatchAlreadyStarted();
    if (maps.find(map_name) == maps.end())
        throw MapNotFound();
    matches[match_id]->start_game(maps.at(map_name));
}

uint8_t MonitorMatches::get_number_of_players(uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    return matches[match_id]->get_number_of_players();
}

void MonitorMatches::kill_dead_matches() {
    std::vector<uint> matches_to_delete;
    for (auto& match: matches) {
        if (match.second->has_ended()) {
            match.second->join();
            matches_to_delete.push_back(match.first);
            std::cout << _BLUE << "Match with id: " << _RESET << match.first << _BLUE
                      << " has ended" << _RESET << std::endl;
        }
    }
    for (auto& match_id: matches_to_delete) {
        matches.erase(match_id);
    }
}

MonitorMatches::~MonitorMatches() {}
