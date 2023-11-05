#include <vector>

#include "../common_src/parser.h"
#include "../common_src/constants.h"

#ifndef PARSER_SERVER_H
#define PARSER_SERVER_H

class ParserServer: public Parser {


public:
    ParserServer() = default;

    void parse_sending_command_lobby(Command& command) override;
    
    void parse_sending_command_match(Command& command) override;
};

#endif  // PARSER_SERVER_H
