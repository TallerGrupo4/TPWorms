#ifndef CLIENTE_CONSTANTES_H
#define CLIENTE_CONSTANTES_H

#include "../common_src/constants.h"

enum TargetType : char {
    PlayerType,
    WormType,
    ProjectileType,
    NoneType,
};

enum ArmyColors : char {
    Blue,
    Red,
    Green,
    Yellow,
    Orange,
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

#define SEED_FOR_SRAND_TIME 0

/*MIXER SETTINGS*/

#define AUDIO_HZ_CD_QUALITY 44100
#define MIXER_CHUNKSIZE 2048

/*SOUND SETTINGS*/
#define MIXER_CHANNELS 4
#define SPECIAL_EXPLOSIONS_CHANNEL 0
#define WORM_SOUNDS_CHANNEL 1

/*MUSIC PATHS*/

#define MUSIC_FOREST_PATH SOUNDS_PATH "/forest_music.wav"
#define BACKGROUND_VOLUME 32

/*RESOLUTION MULTIPLIER*/
#define RESOLUTION_MULTIPLIER 6

/*TEXT FONTS*/

#define WORMS_FONT_PATH FONTS_PATH "/unispace bold.ttf"

#define WORM_FONT_SIZE 10

/*COLORS*/

#define RED {255, 0, 0}

#define BLUE {71, 83, 255}

#define YELLOW {255, 187, 15}

#define GREEN {36, 159, 63}

#define ORANGE {255, 102, 25}

#define BLACK {0, 0, 0}

#define WHITE {255, 255, 255}

/*BACKGROUNDS*/

#define BACKGROUND1_PATH BACKGROUND_PATH "/background1.png"

/*CROSSHAIR/MARKER*/

#define CROSSHAIR_DISTANCE_FROM_WORM_CENTER PIX_PER_METER*RESOLUTION_MULTIPLIER*2

#define SECS_FOR_CROSSHAIR_SPRITES 1

#define CROSSHAIR_BLUE_SPRITES_PATH MISC_SPRITES_PATH "/crshairb.png"

#define CROSSHAIR_RED_SPRITES_PATH MISC_SPRITES_PATH "/crshairr.png"

#define CROSSHAIR_GREEN_SPRITES_PATH MISC_SPRITES_PATH "/crshairg.png"

#define CROSSHAIR_YELLOW_SPRITES_PATH MISC_SPRITES_PATH "/crshairy.png"

#define CROSSHAIR_PURPLE_SPRITES_PATH MISC_SPRITES_PATH "/crshairp.png"

#define SECS_FOR_MARKER_SPRITES 1

#define MARKER_BLUE_SPRITES_PATH MISC_SPRITES_PATH "/markerb.png"

#define MARKER_RED_SPRITES_PATH MISC_SPRITES_PATH "/markerr.png"

#define MARKER_GREEN_SPRITES_PATH MISC_SPRITES_PATH "/markerg.png"

#define MARKER_YELLOW_SPRITES_PATH MISC_SPRITES_PATH "/markery.png"

#define MARKER_PURPLE_SPRITES_PATH MISC_SPRITES_PATH "/markerp.png"

/*WORM ANIMATIONS*/


/*WORM STILL AND MOVING ANIMATIONS*/

#define SECS_FOR_STILL_SPRITES 0

#define WORM_STILL_0_SPRITES_PATH WORMS_SPRITES_PATH "/wdefault.png"

#define WORM_STILL_0_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultd.png"

#define WORM_STILL_0_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultu.png"

#define SECS_FOR_STILL_1_SPRITES 2

#define WORM_STILL_1_SPRITES_PATH WORMS_SPRITES_PATH "/wbrth1.png"

#define SECS_FOR_WALKING_SPRITES 0

#define WORM_WALK_SPRITES_PATH WORMS_SPRITES_PATH "/wwalk.png"

#define WORM_WALK_LEFT_OFFSET 15
#define WORM_WALK_RIGHT_OFFSET 8
#define WORM_WALK_ABOVE_OFFSET 13
#define WORM_WALK_BELLOW_OFFSET 14

#define WORM_WALK_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wwalkd.png"

#define WORM_WALK_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wwalku.png"

#define SECS_FOR_BACKFLIP_SPRITES 1

#define WORM_BACKFLIP_SPRITES_PATH WORMS_SPRITES_PATH "/wbackflp.png"

#define SECS_FOR_JUMP_SPRITES 0

#define WORM_JUMP_SPRITES_PATH WORMS_SPRITES_PATH "/wjump.png"

#define WORM_JUMP_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpd.png"

#define WORM_JUMP_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpu.png"

#define SECS_FOR_FALL_SPRITES 0

#define WORM_FALL_SPRITES_PATH WORMS_SPRITES_PATH "/wfall.png"

#define SECS_FOR_SLIDE_SPRITES 0

#define WORM_SLIDE_SPRITES_PATH WORMS_SPRITES_PATH "/wslide.png"

#define WORM_SLIDE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wslided.png"

#define WORM_SLIDE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wslideu.png"

#define SECS_FOR_DEAD_SPRITES 1

#define WORM_DEAD_SPRITES_PATH MISC_SPRITES_PATH "/grave1.png"

#define SECS_FOR_WIN_SPRITES 0

#define WORM_WIN_SPRITES_PATH WORMS_SPRITES_PATH "/wwinner.png"




/* DEFAULT WORM STILL WITH WEAPONS*/

/*BAZOOKA*/

#define WORM_STILL_BAZOOKA_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefault.png"

#define WORM_STILL_BAZOOKA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefaultd.png"

#define WORM_STILL_BAZOOKA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefaultu.png"

/*MORTAR*/

#define WORM_STILL_MORTAR_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefault.png"

#define WORM_STILL_MORTAR_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefaultd.png"

#define WORM_STILL_MORTAR_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbazdefaultu.png"

/*AIRSTRIKE*/

#define WORM_STILL_AIRSRIKE_SPRITES_PATH WORMS_SPRITES_PATH "/wairdefault.png"

#define WORM_STILL_AIRSRIKE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wairdefaultd.png"

#define WORM_STILL_AIRSRIKE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wairdefaultu.png"

/*TELEPORTATION*/

#define WORM_STILL_TELEPORT_SPRITES_PATH WORMS_SPRITES_PATH "/wteldefault.png"

#define WORM_STILL_TELEPORT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wteldefaultd.png"

#define WORM_STILL_TELEPORT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wteldefaultu.png"

/*EMPTY THROW*/

#define WORM_STILL_EMPTY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrdefault.png"

#define WORM_STILL_EMPTY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrdefaultd.png"

#define WORM_STILL_EMPTY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrdefaultu.png"

/*GREEN_GRENADE*/

#define WORM_STILL_GREEN_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wgrndefault.png"

#define WORM_STILL_GREEN_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wgrndefaultd.png"

#define WORM_STILL_GREEN_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wgrndefaultu.png"

/*RED_GRENADE*/

#define WORM_STILL_RED_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wclsdefault.png"

#define WORM_STILL_RED_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wclsdefaultd.png"

#define WORM_STILL_RED_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wclsdefaultu.png"

/*BANANA*/

#define WORM_STILL_BANANA_SPRITES_PATH WORMS_SPRITES_PATH "/wbandefault.png"

#define WORM_STILL_BANANA_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbandefaultd.png"

#define WORM_STILL_BANANA_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbandefaultu.png"

/*HOLY_GRENADE*/

#define WORM_STILL_HOLY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/whgrdefault.png"

#define WORM_STILL_HOLY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/whgrdefaultd.png"

#define WORM_STILL_HOLY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/whgrdefaultu.png"

/*DYNAMITE*/

#define WORM_STILL_DYNAMITE_SPRITES_PATH WORMS_SPRITES_PATH "/wdyndefault.png"

#define WORM_STILL_DYNAMITE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdyndefaultd.png"

#define WORM_STILL_DYNAMITE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdyndefaultu.png"

/*BASEBALL_BAT*/

#define WORM_STILL_BASEBALL_BAT_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbdefault.png"

#define WORM_STILL_BASEBALL_BAT_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbdefaultd.png"

#define WORM_STILL_BASEBALL_BAT_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wbsbdefaultu.png"


/* WORM WITH WEAPONS CHANGING*/

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

#define WORM_GETTING_EMPTY_GRENADE_SPRITES_PATH WORMS_SPRITES_PATH "/wthrlnk.png"

#define WORM_GETTING_EMPTY_GRENADE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wthrlnkd.png"

#define WORM_GETTING_EMPTY_GRENADE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wthrlnku.png"

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


/* WORM WITH WEAPONS AIMING*/

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


/* WORM WITH WEAPONS ACTIONS*/

/*AIRSTRIKE*/

#define WORM_TALK_AIRSTRIKE_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlk.png"

#define WORM_TALK_AIRSTRIKE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlkd.png"

#define WORM_TALK_AIRSTRIKE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wairtlku.png"

/*TELEPORTATION*/

#define SECS_FOR_TELEPORT_SPRITES 0

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


/*PROVISION BOXES*/

#define PROVISION_BOX_DISGUISE_TYPES 2

#define SECS_FOR_PROVISION_BOXES_SPRITES 1

/*MEDICAL CRATE*/

#define MEDICAL_CRATE_PICKED_SPRITES_PATH MISC_SPRITES_PATH "/mcrate0.png"

#define MEDICAL_CRATE_STILL_SPRITES_PATH MISC_SPRITES_PATH "/mcrate1.png"

/*WEAPON CRATE*/

#define WEAPON_CRATE_PICKED_SPRITES_PATH MISC_SPRITES_PATH "/wcrate0.png"

#define WEAPON_CRATE_STILL_SPRITES_PATH MISC_SPRITES_PATH "/wcrate1.png"

/*WEAPONS AS PROJECTILES START HERE*/

#define SECS_FOR_GRENADES_SPRITES 1
#define SECS_FOR_DYNAMITE_SPRITES 2
#define SECS_FOR_FRAGMENTS_SPRITES 0

/*BAZOOKA*/

#define BAZOOKA_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/missile.png"

/*MORTAR*/

#define MORTAR_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/mortar.png"

/*AIRSTRIKE*/

#define AIRSTRIKE_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/airmisl.png"

/*BANANA*/

#define BANANA_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/banana.png"

/*GREEN_GRENADE*/

#define GREEN_GRENADE_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/grenade.png"

/*DYNAMITE*/

#define DYNAMITE_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/dynamite.png"

/*RED_GRENADE*/

#define RED_GRENADE_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/cluster.png"

/*RED_GRENADE_FRAGMENTS*/

#define RED_GRENADE_FRAGMENTS_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/clustlet.png"

/*HOLY_GRENADE*/

#define HOLY_GRENADE_PROJECTILE_SPRITES_PATH WEAPONS_SPRITES_PATH "/hgrenade.png"


/*EFFECTS (EXPLOSIONS/SMOKE/HITS) START HERE*/

#define SECS_FOR_EXPLOSIONS_SPRITES 0

#define BIG_CIRCLE_EXPLOSION_SPRITES_PATH EFFECTS_SPRITES_PATH "/circle50.png"

#define SMALL_CIRCLE_EXPLOSION_SPRITES_PATH EFFECTS_SPRITES_PATH "/circle25.png"

#define BIG_RING_EXPLOSION_SPRITES_PATH EFFECTS_SPRITES_PATH "/elipse50.png"

#define SMALL_RING_EXPLOSION_SPRITES_PATH EFFECTS_SPRITES_PATH "/elipse25.png"

#define SECS_FOR_EXHAUST_SPRITES 1

#define MISSILE_EXHAUST_SPRITES_PATH EFFECTS_SPRITES_PATH "/hexhaust.png"

#define SECS_FOR_BASEBALL_BAT_HIT_SPRITES 1

#define BASEBALL_BAT_HIT_SPRITES_PATH EFFECTS_SPRITES_PATH "/basehit.png"

#define SECS_FOR_WORM_HIT_SPRITES 1

#define WORM_HIT_SPRITES_PATH EFFECTS_SPRITES_PATH "/wormhit1.png"


/*WEAPONS ICONS START HERE*/

/*BAZOOKA*/

#define BAZOOKA_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/bazooka.1.png"

#define BAZOOKA_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/bazooka.2.png"

/*MORTAR*/

#define MORTAR_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/mortar.1.png"

#define MORTAR_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/mortar.2.png"

/*GREEN_GRENADE*/

#define GREEN_GRENADE_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/grenade.1.png"

#define GREEN_GRENADE_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/grenade.2.png"

/*RED_GRENADE*/

#define RED_GRENADE_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/cluster.1.png"

#define RED_GRENADE_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/cluster.2.png"

/*BANANA*/

#define BANANA_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/banana.1.png"

#define BANANA_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/banana.2.png"

/*HOLY_GRENADE*/

#define HOLY_GRENADE_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/hgrenade.1.png"

#define HOLY_GRENADE_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/hgrenade.2.png"

/*DYNAMITE*/

#define DYNAMITE_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/dynamite.1.png"

#define DYNAMITE_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/dynamite.2.png"

/*BASEBALL_BAT*/

#define BASEBALL_BAT_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/baseball.1.png"

#define BASEBALL_BAT_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/baseball.2.png"

/*AIRSTRIKE*/

#define AIRSTRIKE_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/airstrke.1.png"

#define AIRSTRIKE_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/airstrke.2.png"

/*TELEPORTATION*/

#define TELEPORTATION_ICON_ON_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/teleport.1.png"

#define TELEPORTATION_ICON_OFF_SPRITE_PATH WEAPONSICONS_SPRITES_PATH "/teleport.2.png"


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


/*SOUNDS*/

/*ROUND STARTS*/

#define ROUND_START_SOUND_PATH SOUNDS_PATH "/StartRound.wav"

/*MATCH FINNISHED*/

#define MATCH_FINNISHED_SOUND_PATH SOUNDS_PATH "/CrowdPart1.wav"

/*EXPLOSION SOUNDS*/

#define HOLY_GRENADE_EXPLOSION_SOUND_PATH SOUNDS_PATH "/Explosion1.wav"

#define BIG_EXPLOSION_SOUND_PATH SOUNDS_PATH "/Explosion2.wav"

#define SMALL_EXPLOSION_SOUND_PATH SOUNDS_PATH "/Explosion3.WAV"

/*WEAPON USE SOUNDS*/

#define POWERUP_SOUND_PATH SOUNDS_PATH "/ROCKETPOWERUP.WAV"

#define BAZOOKA_SHOOT_SOUND_PATH SOUNDS_PATH "/ROCKETRELEASE.WAV"

#define DYNAMITE_ACTIVE_SOUND_PATH SOUNDS_PATH "/FUSE.WAV"

#define HOLY_GRENADE_ACTIVE_SOUND_PATH SOUNDS_PATH "/HOLYGRENADE.WAV"

#define AIRSTRIKE_ACTIVE_SOUND_PATH SOUNDS_PATH "/Airstrike.wav"

#define TELEPORT_SOUND_PATH SOUNDS_PATH "/TELEPORT.WAV"

#define BASEBALL_BAT_ACTIVE_SOUND_PATH SOUNDS_PATH "/BaseBallBatRelease.wav"

/*WORM SOUNDS*/

#define WORM_JUMP_SOUND_PATH SOUNDS_PATH "/WORMSPRING.WAV"

#define WORM_IMPACT_SOUND_PATH SOUNDS_PATH "/WORMIMPACT.WAV"

#define WORM_DEATH_SOUND_PATH SOUNDS_PATH "/COUGH5.WAV"

#endif  // CLIENTE_CONSTANTES_H