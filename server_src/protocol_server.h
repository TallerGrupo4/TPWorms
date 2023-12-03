#include <memory>
#include <sys/types.h>
#include "game_src/command_include.h"
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
    const Command recv_create(const char* code);
    const Command recv_join(const char* code);
    const uint recv_match_id();
    const std::string recv_map_name();
    const Command recv_list(const char* code);
    int send_platforms(std::vector<PlatformSnapshot>& platforms);
    int send_map_dimensions(float& _width, float& _height, float& _worm_width, float& _worm_height, int& _amount_of_worms, int& _water_level);
    void send_army(std::map<char, std::vector<char>>& army);
    int send_time_and_worm_turn(const int& _turn_time, const int& _worm_turn);
    int send_worms(std::vector<WormSnapshot>& worms);
    void send_projectiles(std::vector<ProjectileSnapshot>& projectiles);
    void send_end_game(bool end_game);
    void send_provision_boxes(std::vector<ProvisionBoxSnapshot>& provision_boxes);
    void send_armies_health(std::map<char, int>& armies_health);
    std::shared_ptr<GameCommand> recv_mov(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_jump(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_aim(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_shoot(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_change_tool(uint8_t& worm_id);
    std::shared_ptr<GameCommand> recv_cheat(uint8_t& worm_id);

public:
    explicit ProtocolServer(Socket& socket, ParserServer& parser);

    // Lobby
    void send_command(const Command& command);
    const Command recv_command();

    // Match
    int send_snapshot(Snapshot& snapshot);
    std::shared_ptr<GameCommand> recv_game_command();
    bool is_connected() { return !was_closed;}


    bool operator==(const ProtocolServer& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolServer& other) const { return !(*this == other); }
};

#endif  // PROTOCOL_SERVER_H
