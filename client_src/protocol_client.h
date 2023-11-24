#include <cstdint>
#include <memory>
#include <math.h>
#include "../common_src/constants.h"
#include "../common_src/command.h"
#include "../common_src/snapshot.h"
#include "action.h"

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
    std::string recv_map_name();
    std::vector<std::string> recv_map_names();
    uint8_t recv_number_of_players();
    std::map<uint, std::string> recv_list();
    void recv_dimensions(Snapshot& snapshot);
    void recv_platforms(Snapshot& snapshot);
    void recv_army(Snapshot& snapshot);
    void recv_time_and_worm_turn(Snapshot& snapshot);
    void recv_worms(Snapshot& snapshot);
    void send_match_id(const uint match_id);
    void send_map_name(const std::string map_name);

    // PARSER!!!!
    int calculate_beam_width(int degree, float beam_actual_height, float beam_actual_width) {
        return round(beam_actual_height*sin(degree*M_PI/180)+beam_actual_width*cos(degree*M_PI/180));
    }
    int calculate_beam_height(int degree, float beam_actual_height, float beam_actual_width) {
        return round(beam_actual_height*cos(degree*M_PI/180)+beam_actual_width*sin(degree*M_PI/180));
    }
    bool get_degree_of_beam_type(BeamType type, int& degree) {
        switch (type) {
            case LargeVertical:
                return false;
            case Large65:
                degree = 65;
                return true;
            case Large45:
                degree = 45;
                return true;
            case Large25:
                degree = 25;
                return true;
            case LargeHorizontal:
                return false;
            case LargeMinus25:
                degree = 25; // -25?
                return true;
            case LargeMinus45:
                degree = 45;
                return true;
            case LargeMinus65: 
                degree = 65;
                return true;
            case LargeVerticalFlipped:
                return false;
            case ShortVertical:
                return false;
            case Short65:
                degree = 65;
                return true;
            case Short45:
                degree = 45;
                return true;
            case Short25:
                degree = 25;
                return true;
            case ShortHorizontal:
                return false;
            case ShortMinus25:
                degree = 25;
                return true;
            case ShortMinus45:
                degree = 45;
                return true;
            case ShortMinus65:
                degree = 65;
                return true;
            case ShortVerticalFlipped:
                return false;
            default:
                return false;
        }
    };
    // PARSER!!!!


public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    // Lobby
    const Command recv_command();
    void send_command(const Command& command);

    // Match
    Snapshot recv_snapshot();
    void send_action(std::shared_ptr<Action> action);
    // void send_action(Action& action);
    bool is_connected() { return !was_closed;}
    
    bool operator==(const ProtocolClient& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolClient& other) const { return !(*this == other); }
};

#endif  // PROTOCOLO_H