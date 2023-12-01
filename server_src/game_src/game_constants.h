#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Invalid values
#define INVALID -1

//Movement constants 
#define IZQ -1
#define DER 1

//constants for thresholds
#define VEL_THRESHOLD 0.3f
#define ANG_VEL_THRESHOLD 0.5f
#define LAST_ANG_THRESHOLD 30
#define ANG_THRESHOLD 50
#define FALL_DAMAGE_THRESHOLD 25
#define FALL_DISTANCE_THRESHOLD 2
#define MAX_AIMING_ANGLE 90
#define MIN_AIMING_ANGLE -90


enum ExplosionType{
    EXPLOSIVE,
    EXPLOSIVE_TIMER,
    EXPLOSIVE_FRAGMENTS,
    EXPLOSIVE_FRAGMENTS_TIMER,
};

enum BodyType{
    WORM,
    PROJECITLE,
    BEAM,
    PROVISION_BOX,
};



//BUILDER CONSTANTS
#define OFFSET 2


#endif // GAME_CONSTANTS_H