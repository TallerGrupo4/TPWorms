#include "parser_server.h"

#include <sstream>
#include <string>

void ParserServer::parse_sending_command(Command& command) {
    switch (command.code) {
        // This does not make any sense. It is for future parsing...?
        case CASE_CHAT: {
            command.code = CASE_CHAT;
            break;
        }
        case CASE_JOIN: {
            command.code = CASE_JOIN;
            break;
        }
        case CASE_CREATE: {
            command.code = CASE_CREATE;
            break;
        }
        default:
            break;
    }
}
