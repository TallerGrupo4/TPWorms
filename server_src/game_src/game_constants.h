#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define START_LIFE 100
#define NO_WEAPON 0
#define NULL_STATE 0
#define INITIAL_WORMS_TURN 0
#define TURN_TIME 5 * FPS  // SET to 60 seconds!!! 

//Movement constants 
#define IZQ -1
#define DER 1

// defines for physics of game
#define WORM_SPEED 2
#define WORM_JUMP_SPEED 4
#define WORM_JUMP_HOR_SPEED 3
#define WORM_BACKFLIP_SPEED 6
#define WORM_BACKFLIP_HOR_SPEED 1

//constants for thresholds
#define VEL_THRESHOLD 0.05f
#define ANG_VEL_THRESHOLD 0.5f
#define LAST_ANG_THRESHOLD 30
#define ANG_THRESHOLD 50
#define FALL_DAMAGE_THRESHOLD 25
#define FALL_DISTANCE_THRESHOLD 2



enum PROJECTILE_TYPES{
    EXPLOSIVE,
    EXPLOSIVE_TIMER,
    EXPLOSIVE_FRAGMENTS,
    EXPLOSIVE_FRAGMENTS_TIMER,
};

enum BODY_TYPES{
    WORM,
    PROJECITLE,
    PLATFORM
};


//BUILDER CONSTANTS
#define OFFSET 1.5


//--WEAPONS--//
// 1) Bazooka
#define BAZOOKA_DAMAGE 50
#define BAZOOKA_RADIUS 2
#define BAZOOKA_TYPE 1
#define BAZOOKA_MISILE_RESTITUTION 0
#define BAZOOKA_MISILE_DENSITY 0.5

// 2) Mortar
#define MORTAR_DAMAGE 50
#define MORTAR_RADIUS 2
#define MORTAR_TYPE 2
#define MORTAR_FRAGMENTS 6

//3) Green Grenade
#define GREEN_GRENADE_DAMAGE 30
#define GREEN_GRENADE_RADIUS 2
#define GREEN_GRENADE_TYPE 3

//4) Red Grenade
#define RED_GRENADE_DAMAGE 30
#define RED_GRENADE_RADIUS 2
#define RED_GRENADE_TYPE 4
#define RED_GRENADE_FRAGMENTS 6

#endif // GAME_CONSTANTS_H