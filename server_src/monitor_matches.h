#include <map>
#include <memory>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/snapshot.h"

#include "match.h"


#ifndef MONITOR_MATCHES_H
#define MONITOR_MATCHES_H

class MonitorMatches {
private:
    std::map<uint, std::unique_ptr<Match>> matches;
    std::mutex m;

public:
    MonitorMatches();

    // Could return only the Match's queue
    // std::shared_ptr<Queue<GameCommand*>> create_match(std::shared_ptr<Queue<Snapshot>> queue,
    //                                                   uint match_id);
    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> create_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                      uint match_id);

    // std::shared_ptr<Queue<GameCommand*>> join_match(std::shared_ptr<Queue<Snapshot>> queue,
    //                                                 uint match_id);
    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> join_match(std::shared_ptr<Queue<Snapshot>> queue,
                                                    uint match_id);

    void start_match(uint match_id);

    void stop();

    ~MonitorMatches();
};

#endif  // MONITOR_MATCHES_H
