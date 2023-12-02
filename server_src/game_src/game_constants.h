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


// World
// Platforms
#define PLAT_SMALL 3
#define PLAT_BIG 6
#define PLAT_HEIGHT 0.8f
#define PLAT_FRICTION 0.1f

// Worms
#define WORM_WIDTH 1.5f
#define WORM_HEIGHT 1.5f
#define WORM_FRICTION 1.0f


#endif // GAME_CONSTANTS_H