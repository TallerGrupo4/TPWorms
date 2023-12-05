#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <math.h>

#include "../common_src/command.h"
#include "../common_src/constants.h"
#include "../common_src/snapshot.h"

#include "actions.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#include "parser_client.h"

#ifndef PROTOCOLO_H
#define PROTOCOLO_H

class ProtocolClient {

private:
    Socket& socket;
    bool was_closed = false;
    ParserClient& parser;

    void recv_match_id(uint* match_id);
    void recv_number_of_players(uint8_t* number_of_players);
    std::vector<std::string> recv_map_names();
    uint8_t recv_number_of_players();
    std::map<uint, std::string> recv_list();
    void recv_dimensions(Snapshot& snapshot);
    void recv_platforms(Snapshot& snapshot);
    void recv_army(Snapshot& snapshot);
    void recv_time_and_worm_turn(Snapshot& snapshot);
    void recv_projectiles(Snapshot& snapshot);
    void recv_worms(Snapshot& snapshot);
    void recv_end_game(Snapshot& snapshot);
    void recv_provision_boxes(Snapshot& snapshot);
    void recv_armies_health(Snapshot& snapshot);
    void recv_wind_force(Snapshot& snapshot);
    void send_match_id(const uint match_id);
    void send_map_name(const std::string& map_name);


public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    // Lobby
    const Command recv_command();
    void send_command(const Command& command);

    // Match
    Snapshot recv_snapshot();
    void send_action(std::shared_ptr<Action> action);
    bool is_connected() { return !was_closed; }

    bool operator==(const ProtocolClient& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolClient& other) const { return !(*this == other); }
};

#endif  // PROTOCOLO_H
