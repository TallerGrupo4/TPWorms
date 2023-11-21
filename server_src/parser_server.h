#include <vector>

#include "../common_src/parser.h"

#ifndef PARSER_SERVER_H
#define PARSER_SERVER_H

class ParserServer: public Parser {


public:
    ParserServer() = default;

    // void parse_sending_command(Command& command) override;

    // void parse_sending_snapshot(Snapshot& snapshot) override;
};

#endif  // PARSER_SERVER_H
