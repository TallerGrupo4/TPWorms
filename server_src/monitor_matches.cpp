#include "monitor_matches.h"
#include <cstdint>

#include "../common_src/constants.h"
#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

MonitorMatches::MonitorMatches(std::vector<std::string> routes) {
    uint map_id = 1;
    for (auto& route: routes) {
        maps[map_id++] = Map(route);
    }
}

// std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::create_match(std::shared_ptr<Queue<Snapshot>> queue,
//                                                     uint match_id, uint8_t& worm_id, std::vector<std::string>& map_names) {
std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::create_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                      uint match_id, std::vector<uint8_t>& worms_ids, int quantity_of_worms, std::vector<std::string>& map_names) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();

    std::cout << "Creating match with id: " << match_id << std::endl;
    matches[match_id] = std::make_unique<Match>();
    // if (quantity_of_worms > MAX_PLAYERS)
    //     throw TooManyWorms();
    for (int i = 0; i < quantity_of_worms; i++) {
        uint8_t worm_id = matches[match_id]->add_player(queue);
        worms_ids.push_back(worm_id);
    }
    for (auto& map: maps) {
        map_names.push_back(std::to_string(map.first));
    }
    return matches[match_id]->get_queue();
}

void MonitorMatches::stop() {
    std::unique_lock<std::mutex> lock(m);
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
    // Map's key should be a string but for now it is an uint
    // Check if map exists
    uint map_name_int = std::stoi(map_name);
    if (maps.find(std::stoi(map_name)) == maps.end())
        throw MapNotFound();
    matches[match_id]->start_game(maps.at(map_name_int));
}

uint8_t MonitorMatches::get_number_of_players(uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    return matches[match_id]->get_number_of_players();
}

// std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::join_match(std::shared_ptr<Queue<Snapshot>> queue,
//                                                 uint match_id, uint8_t& worm_id, std::vector<std::string>& map_names, uint8_t& number_of_players) {
std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::join_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                      uint match_id, std::vector<uint8_t>& worms_ids, int quantity_of_worms, std::vector<std::string>& map_names, uint8_t& number_of_players) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    // if ((quantity_of_worms + matches[match_id]->get_number_of_players()) > MAX_PLAYERS)
    //     throw TooManyWorms();
    for (int i = 0; i < quantity_of_worms; i++) {
        uint8_t worm_id = matches[match_id]->add_player(queue);
        worms_ids.push_back(worm_id);
        // worms_ids.push_back(matches[match_id]->add_player(queue));
    }
    // worm_id = matches[match_id]->add_player(queue);
    number_of_players = matches[match_id]->get_number_of_players();
    // Copy in map names the ids of the maps
    for (auto& map: maps) {
        map_names.push_back(std::to_string(map.first));
    }
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
