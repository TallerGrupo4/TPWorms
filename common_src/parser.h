#include <vector>

#include "constants.h"
#include "command.h"
#include "snapshot.h"
// #include "game_command.h"
#include "../client_src/actions.h"
// #include "../server_src/game_src/gameCommand.h"

#ifndef PARSER_H
#define PARSER_H

class Parser {

public:
    Parser() = default;

    virtual void parse_sending_command(Command& command);

    virtual void parse_sending_snapshot(Snapshot& snapshot);

    virtual void parse_sending_action(Action& action);

    virtual void parse_receiving_command_join(Command& command, const char* code,
                                              const uint* match_id,
                                              const uint8_t* number_of_players = nullptr);

    virtual void parse_receiving_command_create(Command& command, const char* code,
                                                const uint* match_id);

    virtual void parse_receiving_command_exit(Command& command, const char* code,
                                              const uint8_t* number_of_players,
                                              const uint8_t* player_index);

    virtual void parse_receiving_command_not_found(Command& command, const char* code,
                                                   const uint* match_id);

    virtual void parse_receiving_command_already_exists(Command& command, const char* code,
                                                        const uint* match_id);

    void parse_receiving_command_chat(Command& command, const char* code, std::vector<char> msg);

    void parse_receiving_command_full(Command& command, const char* code, const uint* match_id);

    ~Parser();
};

#endif  // PARSER_H
