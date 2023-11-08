#include "parser.h"

#include <string>

void Parser::parse_sending_command(Command& command) { return; }

void Parser::parse_sending_snapshot(Snapshot& snapshot) { return; }

void Parser::parse_sending_action(Action& action) { return; }


void Parser::parse_receiving_command_chat(Command& command, const char* code,
                                          std::vector<char> msg) {
    command.code = code[0];
    command.msg = std::string(msg.begin(), msg.end());
}

void Parser::parse_receiving_command_join(Command& command, const char* code, const uint* match_id,
                                          const uint8_t* number_of_players) {
    command.code = code[0];
    command.match_id = match_id[0];
    if (number_of_players != nullptr)
        command.number_of_players = number_of_players[0];
}

void Parser::parse_receiving_command_create(Command& command, const char* code,
                                            const uint* match_id) {
    command.code = code[0];
    command.match_id = match_id[0];
}

void Parser::parse_receiving_command_full(Command& command, const char* code,
                                          const uint* match_id) {
    command.code = code[0];
    command.match_id = match_id[0];
}

void Parser::parse_receiving_command_exit(Command& command, const char* code,
                                          const uint8_t* number_of_players,
                                          const uint8_t* player_index) {
    command.code = code[0];
    command.number_of_players = number_of_players[0];
    command.player_index = player_index[0];
}

void Parser::parse_receiving_command_not_found(Command& command, const char* code,
                                               const uint* match_id) {
    command.code = code[0];
    command.match_id = match_id[0];
}

void Parser::parse_receiving_command_already_exists(Command& command, const char* code,
                                                    const uint* match_id) {
    command.code = code[0];
    command.match_id = match_id[0];
}

Parser::~Parser() {}
