#include "parser_client.h"

#include <iostream>
#include <sstream>
#include <string>

void ParserClient::parse_sending_command(Command& command) {
    // std::istringstream str(command.msg);
    // std::string type;
    // str >> type;
    // if (type == CREATE) {
    //     command.code = CASE_CREATE;
    //     str >> command.match_id;
    // } else if (type == JOIN) {
    //     command.code = CASE_JOIN;
    //     str >> command.match_id;
    // } else if (type == EXIT) {
    //     command.code = CASE_EXIT;
    // } else {
    //     command.code = CASE_INVALID;
    // }
}

// void ParserClient::parse_sending_action(Action& action) {
//     std::istringstream str(action.msg);
//     std::getline(str >> std::ws, action.msg, '\0');
//     action.code = CASE_CHAT;
//     if (action.msg == EXIT) action.code = CASE_EXIT;
//     if (action.msg == START) action.code = CASE_START;
// }
