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

#define RESOLUTION_MULTIPLIER 6

#define WORMS_FONT_PATH FONTS_PATH "/unispace bold.ttf"

#define WORM_FONT_SIZE 10

#define RED {255, 0, 0}

#define BLUE {71, 83, 255}

#define YELLOW {255, 187, 15}

#define GREEN {36, 159, 63}

#define ORANGE {255, 102, 25}

#define BACKGROUND1_PATH BACKGROUND_PATH "/background1.png"

#define WORM_STILL_0_SPRITES_PATH WORMS_SPRITES_PATH "/wdefault.png"

#define WORM_STILL_0_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultd.png"

#define WORM_STILL_0_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wdefaultu.png"

#define WORM_STILL_1_SPRITES_PATH WORMS_SPRITES_PATH "/wbrth1.png"

#define WORM_WALK_SPRITES_PATH WORMS_SPRITES_PATH "/wwalk.png"

#define WORM_WALK_LEFT_OFFSET 15
#define WORM_WALK_RIGHT_OFFSET 8
#define WORM_WALK_ABOVE_OFFSET 13
#define WORM_WALK_BELLOW_OFFSET 14

#define WORM_WALK_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wwalkd.png"

#define WORM_WALK_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wwalku.png"

#define WORM_BACKFLIP_SPRITES_PATH WORMS_SPRITES_PATH "/wbackflp.png"

#define WORM_JUMP_SPRITES_PATH WORMS_SPRITES_PATH "/wjump.png"

#define WORM_JUMP_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpd.png"

#define WORM_JUMP_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wjumpu.png"

#define WORM_FALL_SPRITES_PATH WORMS_SPRITES_PATH "/wfall.png"

#define WORM_SLIDE_SPRITES_PATH WORMS_SPRITES_PATH "/wslide.png"

#define WORM_SLIDE_DOWN_SPRITES_PATH WORMS_SPRITES_PATH "/wslided.png"

#define WORM_SLIDE_UP_SPRITES_PATH WORMS_SPRITES_PATH "/wslideu.png"

#define WORM_DEAD_SPRITES_PATH MISC_SPRITES_PATH "/grave1.png"

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