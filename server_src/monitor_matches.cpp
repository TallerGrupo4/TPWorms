#include "monitor_matches.h"

#include "../common_src/constants.h"
#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

class MapNotFound: public std::exception {
    const char* what() const noexcept override {
        return "Was not able to find Map with that id when creating the match";
    }
};

MonitorMatches::MonitorMatches(std::vector<std::string> routes) {
    maps[(uint)1] = Map(routes[0]);
}

std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> MonitorMatches::create_match(
        std::shared_ptr<Queue<Snapshot>> queue, uint match_id, uint8_t& worm_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) != matches.end())
        throw MatchAlreadyExists();

    // HARDCODEO PORQUE NO ESTA IMPLEMENTADO LA ELECCION DEL MAPA
    std::cout << "Creating match with id: " << match_id << std::endl;
    if (maps.find((uint)1) == maps.end()) {
        throw MapNotFound();
    }
    // The map should be passed in the start() method
    matches[match_id] = std::make_unique<Match>(maps.at(1));
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
    matches[match_id]->start_game();
}

uint8_t MonitorMatches::get_number_of_players(uint match_id) {
    std::unique_lock<std::mutex> lock(m);
    if (matches.find(match_id) == matches.end())
        throw MatchNotFound();
    return matches[match_id]->get_number_of_players();
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
