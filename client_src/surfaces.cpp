#include "surfaces.h"

using namespace SDL2pp;

MatchSurfaces::MatchSurfaces() : background1(BACKGROUND1_PATH),
                                still_0_worm(WORM_STILL_0_SPRITES_PATH),
                                still_0_up_worm(WORM_STILL_0_UP_SPRITES_PATH),
                                still_0_down_worm(WORM_STILL_0_DOWN_SPRITES_PATH),
                                still_1_worm(WORM_STILL_1_SPRITES_PATH),
                                walking_worm(WORM_WALK_SPRITES_PATH),
                                walking_up_worm(WORM_WALK_UP_SPRITES_PATH),
                                walking_down_worm(WORM_WALK_DOWN_SPRITES_PATH),
                                backflip_worm(WORM_BACKFLIP_SPRITES_PATH),
                                jump_worm(WORM_JUMP_SPRITES_PATH),
                                jump_up_worm(WORM_JUMP_UP_SPRITES_PATH),
                                jump_down_worm(WORM_JUMP_DOWN_SPRITES_PATH),
                                fall_worm(WORM_FALL_SPRITES_PATH),
                                slide_worm(WORM_SLIDE_SPRITES_PATH),
                                slide_up_worm(WORM_SLIDE_UP_SPRITES_PATH),
                                slide_down_worm(WORM_SLIDE_DOWN_SPRITES_PATH),
                                dead_worm(WORM_DEAD_SPRITES_PATH),
                                still_baz_worm(WORM_STILL_BAZOOKA_SPRITES_PATH),
                                get_baz_worm(WORM_GETTING_BAZOOKA_SPRITES_PATH),
                                get_baz_up_worm(WORM_GETTING_BAZOOKA_UP_SPRITES_PATH),
                                get_baz_down_worm(WORM_GETTING_BAZOOKA_DOWN_SPRITES_PATH),
                                drop_baz_worm(WORM_DROPPING_BAZOOKA_SPRITES_PATH),
                                drop_baz_up_worm(WORM_DROPPING_BAZOOKA_UP_SPRITES_PATH),
                                drop_baz_down_worm(WORM_DROPPING_BAZOOKA_DOWN_SPRITES_PATH),
                                aim_baz_worm(WORM_AIMING_BAZOOKA_SPRITES_PATH),
                                aim_baz_up_worm(WORM_AIMING_BAZOOKA_UP_SPRITES_PATH),
                                aim_baz_down_worm(WORM_AIMING_BAZOOKA_DOWN_SPRITES_PATH),
                                large_beam_vertical(BEAM_LARGE_VERTICAL),
                                large_beam_65(BEAM_LARGE_65),
                                large_beam_45(BEAM_LARGE_45),
                                large_beam_25(BEAM_LARGE_25),
                                large_beam_horizontal(BEAM_LARGE_HORIZONTAL),
                                large_beam_m_25(BEAM_LARGE_MINUS_25),
                                large_beam_m_45(BEAM_LARGE_MINUS_45),
                                large_beam_m_65(BEAM_LARGE_MINUS_65),
                                large_beam_vertical_flipped(BEAM_LARGE_VERTICAL_FLIPPED),
                                short_beam_vertical(BEAM_SHORT_VERTICAL),
                                short_beam_65(BEAM_SHORT_65),
                                short_beam_45(BEAM_SHORT_45),
                                short_beam_25(BEAM_SHORT_25),
                                short_beam_horizontal(BEAM_SHORT_HORIZONTAL),
                                short_beam_m_25(BEAM_SHORT_MINUS_25),
                                short_beam_m_45(BEAM_SHORT_MINUS_45),
                                short_beam_m_65(BEAM_SHORT_MINUS_65),
                                short_beam_vertical_flipped(BEAM_SHORT_VERTICAL_FLIPPED) {
    still_0_worm.SetColorKey(true, 0);
    still_0_up_worm.SetColorKey(true, 0);
    still_0_down_worm.SetColorKey(true, 0);
    still_1_worm.SetColorKey(true, 0);
    walking_worm.SetColorKey(true, 0);
    walking_up_worm.SetColorKey(true, 0);
    walking_down_worm.SetColorKey(true, 0);
    backflip_worm.SetColorKey(true, 0);
    jump_worm.SetColorKey(true, 0);
    jump_up_worm.SetColorKey(true, 0);
    jump_down_worm.SetColorKey(true, 0);
    fall_worm.SetColorKey(true, 0);
    slide_worm.SetColorKey(true, 0);
    slide_up_worm.SetColorKey(true, 0);
    slide_down_worm.SetColorKey(true, 0);
    dead_worm.SetColorKey(true, 0);
    /*WORM STILL STANCE WEAPONS*/
    still_baz_worm.SetColorKey(true, 0);
    /*WORM CHANGING WEAPONS*/
    get_baz_worm.SetColorKey(true, 0);
    get_baz_up_worm.SetColorKey(true, 0);
    get_baz_down_worm.SetColorKey(true, 0);
    drop_baz_worm.SetColorKey(true, 0);
    drop_baz_up_worm.SetColorKey(true, 0);
    drop_baz_down_worm.SetColorKey(true, 0);
    /*WORM AIMING WEAPONS*/
    aim_baz_worm.SetColorKey(true, 0);
    aim_baz_up_worm.SetColorKey(true, 0);
    aim_baz_down_worm.SetColorKey(true, 0);
    /*BEAMS*/
    large_beam_vertical.SetColorKey(true, 0);
    large_beam_65.SetColorKey(true, 0);
    large_beam_45.SetColorKey(true, 0);
    large_beam_25.SetColorKey(true, 0);
    large_beam_horizontal.SetColorKey(true, 0);
    large_beam_m_25.SetColorKey(true, 0);
    large_beam_m_45.SetColorKey(true, 0);
    large_beam_m_65.SetColorKey(true, 0);
    large_beam_vertical_flipped.SetColorKey(true, 0);
    short_beam_vertical.SetColorKey(true, 0);
    short_beam_65.SetColorKey(true, 0);
    short_beam_45.SetColorKey(true, 0);
    short_beam_25.SetColorKey(true, 0);
    short_beam_horizontal.SetColorKey(true, 0);
    short_beam_m_25.SetColorKey(true, 0);
    short_beam_m_45.SetColorKey(true, 0);
    short_beam_m_65.SetColorKey(true, 0);
    short_beam_vertical_flipped.SetColorKey(true, 0);
}
