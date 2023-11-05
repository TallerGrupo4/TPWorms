#include <string>

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define MAX_PLAYERS 100

// This INVALID macro is only used to initialize the Command struct
#define DEFAULT 0x00
#define INITIALIZE_COMMAND \
    { DEFAULT, "", DEFAULT, DEFAULT, DEFAULT, DEFAULT }

#define SOCKET_FAILED -1
#define WAS_CLOSED -2

// Common codes
#define CASE_CHAT 0x01
#define CASE_CREATE 0x02
#define CASE_JOIN 0x03

// Client codes
#define CASE_EXIT 0x04
#define CASE_INVALID 0x05
#define CREATE "Create"
#define JOIN "Join"
#define CHAT "Chat"
#define EXIT "Exit"

// Server codes
#define CASE_MATCH_ALREADY_EXISTS 0x04
#define CASE_MATCH_FULL 0x05
#define CASE_MATCH_NOT_FOUND 0x06
#define CASE_EXIT_SERVER 0x07

#define QUEUE_MAX_SIZE 1000

struct Command {
    // cppcheck-suppress unusedStructMember
    char code;
    std::string msg;
    // cppcheck-suppress unusedStructMember
    uint8_t number_of_players;
    // cppcheck-suppress unusedStructMember
    uint8_t player_index;
    // cppcheck-suppress unusedStructMember
    int read;
    uint match_id;
};

#endif  // _CONSTANTS_H_
