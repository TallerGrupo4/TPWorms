#include <map>
#include <memory>
#include <vector>

#include "monitor_match.h"
#include "constants.h"
#include "queue.h"


#ifndef MONITOR_MATCHES_H
#define MONITOR_MATCHES_H

class MonitorMatches {
private:
    std::map<uint, std::shared_ptr<MonitorMatch>> matches;
    std::mutex m;

public:
    MonitorMatches();

    std::shared_ptr<MonitorMatch> create(const std::shared_ptr<Queue<Command>> queue,
                                         uint match_id);

    std::shared_ptr<MonitorMatch> join(const std::shared_ptr<Queue<Command>> queue, uint match_id);

    ~MonitorMatches();
};

#endif  // MONITOR_MATCHES_H
