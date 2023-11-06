#include <vector>

#include "../common_src/constants.h"
#include "../common_src/parser.h"

#ifndef PARSER_CLIENT_H
#define PARSER_CLIENT_H

class ParserClient: public Parser {


public:
    ParserClient() = default;

    void parse_sending_command_lobby(Command& command) override;

    void parse_sending_command_match(Command& command) override;
};

#endif  // PARSER_CLIENT_H
