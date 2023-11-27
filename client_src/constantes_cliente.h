#ifndef CLIENTE_CONSTANTES_H
#define CLIENTE_CONSTANTES_H

enum TargetType : char {
    PlayerType,
    WormType,
    ProjectileType,
    NoneType,
};

struct Target {
    TargetType type_of_target = NoneType;
    int worm_id = -1;
    int projectile_id = -1;
    int x_offset = 0;
    int y_offset = 0;
};

#define DOWN -0x01
#define CENTER 0x00
#define UP 0x01
#define SCROLL_UP 0x01
#define SCROLL_DOWN -0x01

#define RESOLUTION_MULTIPLIER 6

#define WORMS_FONT_PATH FONTS_PATH "/unispace bold.ttf"

#define WORM_FONT_SIZE 10

#define RED {255, 0, 0}

#define BLUE {71, 83, 255}

#define YELLOW {255, 187, 15}

#define GREEN {36, 159, 63}

#define ORANGE {255, 102, 25}

#define BACKGROUND1_PATH BACKGROUND_PATH "/background1.png"

#define SECS_FOR_STILL_SPRITES 0

#define WORM_STILL_0_SPRITES_PATH WORMS_SPRITES_PATH "/wdefault.png"

#define WORM_STILL_0_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultd.png"

#define WORM_STILL_0_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultu.png"

#define SECS_FOR_STILL_1_SPRITES 2

#define WORM_STILL_1_SPRITES_PATH WORMS_SPRITES_PATH "/wbrth1.png"

#define SECS_FOR_WALKING_SPRITES 1

#define WORM_WALK_SPRITES_PATH WORMS_SPRITES_PATH "/wwalk.png"

#define WORM_WALK_LEFT_OFFSET 15
#define WORM_WALK_RIGHT_OFFSET 8
#define WORM_WALK_ABOVE_OFFSET 13
#define WORM_WALK_BELLOW_OFFSET 14

#define WORM_WALK_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wwalkd.png"

#define WORM_WALK_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wwalku.png"

#define SECS_FOR_BACKFLIP_SPRITES 1

#define WORM_BACKFLIP_SPRITES_PATH WORMS_SPRITES_PATH "/wbackflp.png"

#define SECS_FOR_JUMP_SPRITES 1

#define WORM_JUMP_SPRITES_PATH WORMS_SPRITES_PATH "/wjump.png"

#define WORM_JUMP_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpd.png"

#define WORM_JUMP_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpu.png"

#define SECS_FOR_FALL_SPRITES 0

#define WORM_FALL_SPRITES_PATH WORMS_SPRITES_PATH "/wfall.png"

#define SECS_FOR_SLIDE_SPRITES 0

#define WORM_SLIDE_SPRITES_PATH WORMS_SPRITES_PATH "/wslide.png"

#define WORM_SLIDE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wslided.png"

#define WORM_SLIDE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wslideu.png"

#define SECS_FOR_DEAD_SPRITES 2

#define WORM_DEAD_SPRITES_PATH MISC_SPRITES_PATH "/grave1.png"


/* WEAPONS CHANGING CONSTANTS START HERE*/

/*BAZOOKA*/

#define WORM_GETTING_BAZOOKA_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnk.png"

#define WORM_GETTING_BAZOOKA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnkd.png"

#define WORM_GETTING_BAZOOKA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnku.png"

#define WORM_DROPPING_BAZOOKA_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbak.png"

#define WORM_DROPPING_BAZOOKA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbakd.png"

#define WORM_DROPPING_BAZOOKA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbaku.png"

/*MORTAR*/

#define WORM_GETTING_MORTAR_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnk.png"

#define WORM_GETTING_MORTAR_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnkd.png"

#define WORM_GETTING_MORTAR_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazlnku.png"

#define WORM_DROPPING_MORTAR_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbak.png"

#define WORM_DROPPING_MORTAR_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbakd.png"

#define WORM_DROPPING_MORTAR_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazbaku.png"

/*AIRSTRIKE*/

#define WORM_GETTING_AIRSRIKE_SPRITES_PATH WORMS_SPRITES_PATH "/wairlnk.png"

#define WORM_GETTING_AIRSRIKE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wairlnkd.png"

#define WORM_GETTING_AIRSRIKE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wairlnku.png"

#define WORM_DROPPING_AIRSRIKE_SPRITES_PATH WORMS_SPRITES_PATH "/wairbak.png"

#define WORM_DROPPING_AIRSRIKE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wairbakd.png"

#define WORM_DROPPING_AIRSRIKE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wairbaku.png"

/*TELEPORTATION*/

#define WORM_GETTING_TELEPORT_SPRITES_PATH WORMS_SPRITES_PATH "/wtellnk.png"

#define WORM_GETTING_TELEPORT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wtellnkd.png"

#define WORM_GETTING_TELEPORT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wtellnku.png"

#define WORM_DROPPING_TELEPORT_SPRITES_PATH WORMS_SPRITES_PATH "/wtelbak.png"

#define WORM_DROPPING_TELEPORT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wtelbakd.png"

#define WORM_DROPPING_TELEPORT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wtelbaku.png"

/*EMPTY THROW*/

#define WORM_DROPPING_EMPTY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrbak.png"

#define WORM_DROPPING_EMPTY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrbakd.png"

#define WORM_DROPPING_EMPTY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrbaku.png"

/*GREEN_GRENADE*/

#define WORM_GETTING_GREEN_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnlnk.png"

#define WORM_GETTING_GREEN_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnlnkd.png"

#define WORM_GETTING_GREEN_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnlnku.png"

#define WORM_DROPPING_GREEN_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnbak.png"

#define WORM_DROPPING_GREEN_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnbakd.png"

#define WORM_DROPPING_GREEN_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wgrnbaku.png"

/*RED_GRENADE*/

#define WORM_GETTING_RED_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wclslnk.png"

#define WORM_GETTING_RED_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wclslnkd.png"

#define WORM_GETTING_RED_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wclslnku.png"

#define WORM_DROPPING_RED_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wclsbak.png"

#define WORM_DROPPING_RED_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wclsbakd.png"

#define WORM_DROPPING_RED_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wclsbaku.png"

/*BANANA*/

#define WORM_GETTING_BANANA_SPRITES_PATH WORMS_SPRITES_PATH "/wbanlnk.png"

#define WORM_GETTING_BANANA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbanlnkd.png"

#define WORM_GETTING_BANANA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbanlnku.png"

#define WORM_DROPPING_BANANA_SPRITES_PATH WORMS_SPRITES_PATH "/wbanbak.png"

#define WORM_DROPPING_BANANA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbanbakd.png"

#define WORM_DROPPING_BANANA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbanbaku.png"

/*HOLY_GRENADE*/

#define WORM_GETTING_HOLY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/whgrlnk.png"

#define WORM_GETTING_HOLY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/whgrlnkd.png"

#define WORM_GETTING_HOLY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/whgrlnku.png"

#define WORM_DROPPING_HOLY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/whgrbak.png"

#define WORM_DROPPING_HOLY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/whgrbakd.png"

#define WORM_DROPPING_HOLY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/whgrbaku.png"

/*DYNAMITE*/

#define WORM_GETTING_DYNAMITE_SPRITES_PATH WORMS_SPRITES_PATH "/wdynlnk.png"

#define WORM_GETTING_DYNAMITE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdynlnkd.png"

#define WORM_GETTING_DYNAMITE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdynlnku.png"

#define WORM_DROPPING_DYNAMITE_SPRITES_PATH WORMS_SPRITES_PATH "/wdynbak.png"

#define WORM_DROPPING_DYNAMITE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdynbakd.png"

#define WORM_DROPPING_DYNAMITE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdynbaku.png"

/*BASEBALL_BAT*/

#define WORM_GETTING_BASEBALL_BAT_SPRITES_PATH WORMS_SPRITES_PATH "/wbsblnk.png"

#define WORM_GETTING_BASEBALL_BAT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbsblnkd.png"

#define WORM_GETTING_BASEBALL_BAT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbsblnku.png"

#define WORM_DROPPING_BASEBALL_BAT_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbbak.png"

#define WORM_DROPPING_BASEBALL_BAT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbbakd.png"

#define WORM_DROPPING_BASEBALL_BAT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbbaku.png"


/* WEAPONS AIMING START HERE*/

/*BAZOOKA*/

#define WORM_AIMING_BAZOOKA_SPRITES_PATH WORMS_SPRITES_PATH "/wbaz.png"

#define WORM_AIMING_BAZOOKA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazd.png"

#define WORM_AIMING_BAZOOKA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazu.png"

/*MORTAR*/

#define WORM_AIMING_MORTAR_SPRITES_PATH WORMS_SPRITES_PATH "/wbaz.png"

#define WORM_AIMING_MORTAR_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazd.png"

#define WORM_AIMING_MORTAR_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazu.png"

/*EMPTY THROW*/

#define WORM_AIMING_EMPTY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrow.png"

#define WORM_AIMING_EMPTY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrowd.png"

#define WORM_AIMING_EMPTY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrowu.png"

/*GREEN_GRENADE*/

#define WORM_AIMING_GREEN_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrgrn.png"

#define WORM_AIMING_GREEN_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrgrnd.png"

#define WORM_AIMING_GREEN_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrgrnu.png"

/*RED_GRENADE*/

#define WORM_AIMING_RED_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrcls.png"

#define WORM_AIMING_RED_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrclsd.png"

#define WORM_AIMING_RED_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrclsu.png"

/*BANANA*/

#define WORM_AIMING_BANANA_SPRITES_PATH WORMS_SPRITES_PATH "/wthrban.png"

#define WORM_AIMING_BANANA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrband.png"

#define WORM_AIMING_BANANA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrbanu.png"

/*HOLY_GRENADE*/

#define WORM_AIMING_HOLY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrhgr.png"

#define WORM_AIMING_HOLY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrhgrd.png"

#define WORM_AIMING_HOLY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrhgru.png"

/*BASEBALL_BAT*/

#define WORM_AIMING_BASEBALL_BAT_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbaim.png"

#define WORM_AIMING_BASEBALL_BAT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbaimd.png"

#define WORM_AIMING_BASEBALL_BAT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbaimu.png"


/* WEAPONS ACTIONS START HERE*/

/*AIRSTRIKE*/

#define WORM_TALK_AIRSTRIKE_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlk.png"

#define WORM_TALK_AIRSTRIKE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlkd.png"

#define WORM_TALK_AIRSTRIKE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlku.png"

/*TELEPORTATION*/

#define WORM_TALK_TELEPORT_SPRITES_PATH WORMS_SPRITES_PATH "/wteltlk.png"

#define WORM_TALK_TELEPORT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wteltlkd.png"

#define WORM_TALK_TELEPORT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wteltlku.png"

#define WORM_USE_TELEPORT_SPRITES_PATH WORMS_SPRITES_PATH "/wteldsv.png"

#define WORM_USE_TELEPORT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wteldsvd.png"

#define WORM_USE_TELEPORT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wteldsvu.png"


/*BASEBALL_BAT*/

#define WORM_SWING_BASEBALL_BAT_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbswn.png"

#define WORM_SWING_BASEBALL_BAT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbswnd.png"

#define WORM_SWING_BASEBALL_BAT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbswnu.png"


/* BEAMS CONSTANTS START HERE*/

#define BEAM_LARGE_VERTICAL WEAPONS_SPRITES_PATH "/grdl0.png"

#define BEAM_LARGE_65 WEAPONS_SPRITES_PATH "/grdl1.png"

#define BEAM_LARGE_45 WEAPONS_SPRITES_PATH "/grdl2.png"

#define BEAM_LARGE_25 WEAPONS_SPRITES_PATH "/grdl3.png"

#define BEAM_LARGE_HORIZONTAL WEAPONS_SPRITES_PATH "/grdl4.png"

#define BEAM_LARGE_MINUS_25 WEAPONS_SPRITES_PATH "/grdl5.png"

#define BEAM_LARGE_MINUS_45 WEAPONS_SPRITES_PATH "/grdl6.png"

#define BEAM_LARGE_MINUS_65 WEAPONS_SPRITES_PATH "/grdl7.png"

#define BEAM_LARGE_VERTICAL_FLIPPED WEAPONS_SPRITES_PATH "/grdl8.png"

#define BEAM_SHORT_VERTICAL WEAPONS_SPRITES_PATH "/grds0.png"

#define BEAM_SHORT_65 WEAPONS_SPRITES_PATH "/grds1.png"

#define BEAM_SHORT_45 WEAPONS_SPRITES_PATH "/grds2.png"

#define BEAM_SHORT_25 WEAPONS_SPRITES_PATH "/grds3.png"

#define BEAM_SHORT_HORIZONTAL WEAPONS_SPRITES_PATH "/grds4.png"

#define BEAM_SHORT_MINUS_25 WEAPONS_SPRITES_PATH "/grds5.png"

#define BEAM_SHORT_MINUS_45 WEAPONS_SPRITES_PATH "/grds6.png"

#define BEAM_SHORT_MINUS_65 WEAPONS_SPRITES_PATH "/grds7.png"

#define BEAM_SHORT_VERTICAL_FLIPPED WEAPONS_SPRITES_PATH "/grds8.png"

#endif  // CLIENTE_CONSTANTES_H