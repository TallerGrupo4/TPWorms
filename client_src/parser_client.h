#include <vector>

#include "../common_src/parser.h"
#include "../common_src/constants.h"

#ifndef PARSER_CLIENT_H
#define PARSER_CLIENT_H

class ParserClient: public Parser {


public:
    ParserClient() = default;

    void parse_sending_command(Command& command) override;
};

#endif  // PARSER_CLIENT_H
