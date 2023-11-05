#include "parser_client.h"

#include <iostream>
#include <sstream>
#include <string>

void ParserClient::parse_sending_command_lobby(Command& command) {
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

void ParserClient::parse_sending_command_match(Command& command) {
    std::istringstream str(command.msg);
    std::string type;
    str >> type;
    if (type == CHAT) {
        command.code = CASE_CHAT;
        std::getline(str >> std::ws, command.msg, '\0');
    } else if (type == EXIT) {
        command.code = CASE_EXIT;
    } else {
        command.code = CASE_INVALID;
    }
}
