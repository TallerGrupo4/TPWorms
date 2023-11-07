#include "parser_client.h"

#include <iostream>
#include <sstream>
#include <string>

void ParserClient::parse_sending_command(Command& command) {
    std::istringstream str(command.msg);
    std::string type;
    str >> type;
    if (type == CREATE) {
        command.code = CASE_CREATE;
        str >> command.match_id;
    } else if (type == JOIN) {
        command.code = CASE_JOIN;
        str >> command.match_id;
    } else if (type == EXIT) {
        command.code = CASE_EXIT;
    } else {
        command.code = CASE_INVALID;
    }
}

void ParserClient::parse_sending_game_command(GameCommand& game_command) {
    std::istringstream str(game_command.msg);
    std::getline(str >> std::ws, game_command.msg, '\0');
    game_command.code = CASE_CHAT;
    if (game_command.msg == EXIT) game_command.code = CASE_EXIT;
    if (game_command.msg == START) game_command.code = CASE_START;
}
