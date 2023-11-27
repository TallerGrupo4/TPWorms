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
#define CASE_STARTING_MATCH 0x14

// Client codes
#define CREATE "Create"
#define JOIN "Join"
#define EXIT "Exit"

// Queue codes DO NOT CHANGE
#define QUEUE_MAX_SIZE 10000


//Common worm States
enum WormStates : char {
    STILL,
    MOVING,
    JUMPI,
    BackflippingState,
    FallingState, 
    ClimbingState, 
    SlidingState, 
    AimingState,
    DamagedState, 
    DeadState
};



enum ProjectileStates : char {
    ALIVE,
    EXPLODING,
    EXPLODED,
};

enum TOOLS : uint8_t {
    BAZOOKA,
    MORTAR,
    GREEN_GRENADE,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    RED_GRENADE,
    BANANA,
    AIRSTRIKE,
    TELEPORTATION,
    NO_TOOL,
};

#define STILL 0
#define MOVING 1
#define JUMPING 2
#define BACKFLIPPING 3
#define FALLING 4
#define CLIMBING 5
#define SLIDING 6
#define DAMAGED 7
#define DEAD 8
#define AIMING 9
#define SHOOTED 10


// Codes for game actions common to client and server
#define MOV 0x01
#define LEFT -0x01
#define RIGHT 0x01
#define JUMP 0x03
#define BACKFLIP 0x04
#define FOWARD 0x01
#define BACKWARD -0x01
#define SHOOT 0x05
#define AIM 0x06

// START OF YAML -------------------------

// Platforms codes
#define PLAT_SMALL 3
#define PLAT_BIG 6
#define PLAT_HEIGHT 0.8
#define PLAT_FRICTION 0.1

// Worms codes
#define WORM_WIDTH 1.5f
#define WORM_HEIGHT 1.5f
#define WORM_FRICTION 1

// END OF YAML ----------------------------



// Codes for protocol
#define MULTIPLIER 1000.0f // to convert from float to int for protocol taking into account 3 decimal places
#define MAP 0x01
#define WORMS 0x02


//Consts for render
#define PIX_PER_METER 6.0f


// START OF YAML -------------------------

// Consts for game loop
#define FPS 30.0f
#define FRAME_TIME 1.0f / FPS
// END OF YAML --------------------------------
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.14159265358979323846f



#endif  // _CONSTANTS_H_
