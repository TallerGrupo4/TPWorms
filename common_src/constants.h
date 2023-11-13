#include <string>

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define MAX_PLAYERS 4

// This DEFAULT macro is only used to initialize the Command struct
#define DEFAULT 0x00
#define INITIALIZE_COMMAND \
    { DEFAULT, "", DEFAULT, DEFAULT, DEFAULT, DEFAULT }

#define SOCKET_FAILED -1
#define WAS_CLOSED -2

// Common codes
#define CASE_CHAT 0x01
#define CASE_CREATE 0x02
#define CASE_JOIN 0x03
#define CASE_START 0x04

// Client codes
#define CASE_EXIT 0x05
#define CASE_INVALID 0x06
#define CREATE "Create"
#define JOIN "Join"
#define CHAT "Chat"
#define EXIT "Exit"
#define _START "Start"

// Server codes
#define CASE_MATCH_ALREADY_EXISTS 0x04
#define CASE_MATCH_FULL 0x05
#define CASE_MATCH_NOT_FOUND 0x06
#define CASE_EXIT_SERVER 0x07
// Remember that if a a client exited the server, it will not send to the server a msg,
// but instead, the socket will fail and the server will detect it, removing it from the
// list of clients, match, etc. (Whatever is needed) 

#define QUEUE_MAX_SIZE 1000

// Create constructors for the Command based on the code
// Make every attribute of the struct constant after initialization
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

// defines for physics of game
#define WORM_SPEED 0.4

// Codes for game actions
#define MOV 0x01


// Code for protocol
#define MULTIPLIER 1000 // to convert from float to int for protocol taking into account 3 decimal places
#define MAP 0x01
#define WORMS 0x02
#define START 0x03


#endif  // _CONSTANTS_H_