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
    std::string recv_map_name();
    std::map<uint, std::string> recv_list();
    Snapshot recv_platforms();
    Snapshot recv_worms();
    uint8_t recv_worm_id();

public:
    explicit ProtocolClient(Socket& socket, ParserClient& parser);

    // Lobby
    const Command recv_command();
    void send_command(const Command& command);

    // Match
    Snapshot recv_snapshot();
    void send_action(Action& action);
    bool is_connected() { return !was_closed;}
    
    bool operator==(const ProtocolClient& other) const { return this->socket == other.socket; }
    bool operator!=(const ProtocolClient& other) const { return !(*this == other); }
};

#endif  // PROTOCOLO_H