#include <cstdint>
#include <string>

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define MAX_PLAYERS 4

// This DEFAULT macro is only used to initialize the Command struct
#define DEFAULT 0x00

#define SOCKET_FAILED -1
#define WAS_CLOSED -2

// Common codes
#define CASE_CHAT 0x01
#define CASE_CREATE 0x02
#define CASE_START 0x03
#define CASE_JOIN 0x04
#define CASE_LIST 0x05
#define CASE_NUMBER_OF_PLAYERS 0x06
#define CASE_EXIT 0x07
#define CASE_INVALID 0x08
#define CASE_MATCH_ALREADY_EXISTS 0x09
#define CASE_MATCH_FULL 0x10
#define CASE_MATCH_NOT_FOUND 0x11
#define CASE_MATCH_ALREADY_STARTED 0x12
#define CASE_EXIT_SERVER 0x13

// Client codes
#define CREATE "Create"
#define JOIN "Join"
#define EXIT "Exit"
#define _START "Start"

// Server codes
// Remember that if a a client exited the server, it will not send to the server a msg,
// but instead, the socket will fail and the server will detect it, removing it from the
// list of clients, match, etc. (Whatever is needed) 

#define QUEUE_MAX_SIZE 1000

//Common Weapon states
#define NO_WEAPON 0

//Common worm States
#define STILL 0
#define MOVING 1
#define JUMPING 2
#define BACKFLIPPING 3
#define FALLING 4

// Codes for game actions
#define MOV 0x01
#define LEFT -0x01
#define RIGHT 0x01
#define JUMP 0x03
#define BACKFLIP 0x04
#define SHOOT 0x05

// Platforms codes
#define PLAT_SMALL 3
#define PLAT_BIG 6
#define PLAT_HEIGHT 0.8
#define PLAT_FRICTION 0.5

// Worms codes
#define WORM_WIDTH 2
#define WORM_HEIGHT 2
#define WORM_FRICTION 0.5

// Code for protocol
#define MULTIPLIER 1000.0f // to convert from float to int for protocol taking into account 3 decimal places
#define MAP 0x01
#define WORMS 0x02
#define ACTION_EXIT 0x03


//Consts for render
#define PIX_PER_METER 6.0f

// Consts for game loop
#define FPS 30
#define FRAME_TIME 0.01666666666f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#endif  // _CONSTANTS_H_
