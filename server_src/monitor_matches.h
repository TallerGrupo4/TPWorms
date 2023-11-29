#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshot.h"

#include "match.h"
#include "map.h"


#ifndef MONITOR_MATCHES_H
#define MONITOR_MATCHES_H

class MonitorMatches {
private:
    // This should be a list of maps
    std::map<uint, std::unique_ptr<Match>> matches;
    std::map<uint, Map> maps;
    std::mutex m;

    void kill_dead_matches();

public:
    MonitorMatches(std::vector<std::string> routes);
    
    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> create_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                      uint match_id, uint8_t& number_of_players, std::vector<std::string>& map_names, uint8_t& army_id);

    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> join_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                      uint match_id, uint8_t& number_of_players, std::vector<std::string>& map_names, uint8_t& army_id);


    std::map<uint, std::string> list_matches();

    void start_match(uint match_id, std::string map_name);

    uint8_t get_number_of_players(uint match_id);

    void stop();

    ~MonitorMatches();
};

#endif  // MONITOR_MATCHES_H
