#include <memory>
#include <sys/types.h>
#include "game_src/game_command.h"
#include "../common_src/snapshot.h"
#include "../common_src/constants.h"
#include "../common_src/command.h"

#include "parser_server.h"

#ifdef TESTING
#include "../common_src/dummy_socket.h"
#else
#include "../common_src/socket.h"
#endif

#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

class ProtocolServer {

private:
    Socket& socket;
    bool was_closed = false;
    ParserServer& parser;

private:
    void send_match_id(const uint _match_id);
    void send_number_of_players(const uint8_t number_of_players);
    void send_list(const std::map<uint, std::string>& matches_availables);
    void send_map_name(const std::string map_name);
    void send_map_names(const std::vector<std::string>& map_names);
    void send_worm_id(const uint8_t worm_id);
    const Command recv_create(const char* code);
    const Command recv_join(const char* code);
    const uint recv_match_id();
    const std::string recv_map_name();
    const Command recv_list(const char* code);
    int send_platforms(std::vector<PlatformSnapshot>& platforms);
    int send_map_dimensions(const float& _width, const float& _height, const float& _worm_width, const float& _worm_height);
    int send_time_and_worm_turn(const int& _turn_time, const int& _worm_turn);
    int send_worms(std::vector<WormSnapshot>& worms);
    std::shared_ptr<GameCommand> recv_mov(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_jump(uint8_t& worm_id);

public:
    explicit ProtocolServer(Socket& socket, ParserServer& parser);

    // Lobby
    void send_command(const Command& command);
    const Command recv_command();

    // Match
    int send_snapshot(Snapshot& snapshot);
    std::shared_ptr<GameCommand> recv_game_command(uint8_t& worm_id);
    bool is_connected() { return !was_closed;}


    bool operator==(const ProtocolServer& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolServer& other) const { return !(*this == other); }
};

#endif  // PROTOCOL_SERVER_H
