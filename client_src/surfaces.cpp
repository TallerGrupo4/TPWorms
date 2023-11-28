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
                                /*WORM STILL STANCE WEAPONS*/
                                still_baz_worm(WORM_STILL_BAZOOKA_SPRITES_PATH),
                                still_baz_up_worm(WORM_STILL_BAZOOKA_UP_SPRITES_PATH),
                                still_baz_down_worm(WORM_STILL_BAZOOKA_DOWN_SPRITES_PATH),
                                still_mortar_worm(WORM_STILL_MORTAR_SPRITES_PATH),
                                still_mortar_up_worm(WORM_STILL_MORTAR_UP_SPRITES_PATH),
                                still_mortar_down_worm(WORM_STILL_MORTAR_DOWN_SPRITES_PATH),
                                still_air_worm(WORM_STILL_AIRSRIKE_SPRITES_PATH),
                                still_air_up_worm(WORM_STILL_AIRSRIKE_UP_SPRITES_PATH),
                                still_air_down_worm(WORM_STILL_AIRSRIKE_DOWN_SPRITES_PATH),
                                still_tel_worm(WORM_STILL_TELEPORT_SPRITES_PATH),
                                still_tel_up_worm(WORM_STILL_TELEPORT_UP_SPRITES_PATH),
                                still_tel_down_worm(WORM_STILL_TELEPORT_DOWN_SPRITES_PATH),
                                still_thr_worm(WORM_STILL_EMPTY_GRENADE_SPRITES_PATH),
                                still_thr_up_worm(WORM_STILL_EMPTY_GRENADE_UP_SPRITES_PATH),
                                still_thr_down_worm(WORM_STILL_EMPTY_GRENADE_DOWN_SPRITES_PATH),
                                still_grn_worm(WORM_STILL_GREEN_GRENADE_SPRITES_PATH),
                                still_grn_up_worm(WORM_STILL_GREEN_GRENADE_UP_SPRITES_PATH),
                                still_grn_down_worm(WORM_STILL_GREEN_GRENADE_DOWN_SPRITES_PATH),
                                still_cls_worm(WORM_STILL_RED_GRENADE_SPRITES_PATH),
                                still_cls_up_worm(WORM_STILL_RED_GRENADE_UP_SPRITES_PATH),
                                still_cls_down_worm(WORM_STILL_RED_GRENADE_DOWN_SPRITES_PATH),
                                still_ban_worm(WORM_STILL_BANANA_SPRITES_PATH),
                                still_ban_up_worm(WORM_STILL_BANANA_UP_SPRITES_PATH),
                                still_ban_down_worm(WORM_STILL_BANANA_DOWN_SPRITES_PATH),
                                still_hgr_worm(WORM_STILL_HOLY_GRENADE_SPRITES_PATH),
                                still_hgr_up_worm(WORM_STILL_HOLY_GRENADE_UP_SPRITES_PATH),
                                still_hgr_down_worm(WORM_STILL_HOLY_GRENADE_DOWN_SPRITES_PATH),
                                still_dyn_worm(WORM_STILL_DYNAMITE_SPRITES_PATH),
                                still_dyn_up_worm(WORM_STILL_DYNAMITE_UP_SPRITES_PATH),
                                still_dyn_down_worm(WORM_STILL_DYNAMITE_DOWN_SPRITES_PATH),
                                still_bsb_worm(WORM_STILL_BASEBALL_BAT_SPRITES_PATH),
                                still_bsb_up_worm(WORM_STILL_BASEBALL_BAT_UP_SPRITES_PATH),
                                still_bsb_down_worm(WORM_STILL_BASEBALL_BAT_DOWN_SPRITES_PATH),
                                /*WORM CHANGING WEAPONS*/
                                get_baz_worm(WORM_GETTING_BAZOOKA_SPRITES_PATH),
                                get_baz_up_worm(WORM_GETTING_BAZOOKA_UP_SPRITES_PATH),
                                get_baz_down_worm(WORM_GETTING_BAZOOKA_DOWN_SPRITES_PATH),
                                drop_baz_worm(WORM_DROPPING_BAZOOKA_SPRITES_PATH),
                                drop_baz_up_worm(WORM_DROPPING_BAZOOKA_UP_SPRITES_PATH),
                                drop_baz_down_worm(WORM_DROPPING_BAZOOKA_DOWN_SPRITES_PATH),
                                get_mortar_worm(WORM_GETTING_MORTAR_SPRITES_PATH),
                                get_mortar_up_worm(WORM_GETTING_MORTAR_UP_SPRITES_PATH),
                                get_mortar_down_worm(WORM_GETTING_MORTAR_DOWN_SPRITES_PATH),
                                drop_mortar_worm(WORM_DROPPING_MORTAR_SPRITES_PATH),
                                drop_mortar_up_worm(WORM_DROPPING_MORTAR_UP_SPRITES_PATH),
                                drop_mortar_down_worm(WORM_DROPPING_MORTAR_DOWN_SPRITES_PATH),
                                get_air_worm(WORM_GETTING_AIRSRIKE_SPRITES_PATH),
                                get_air_up_worm(WORM_GETTING_AIRSRIKE_UP_SPRITES_PATH),
                                get_air_down_worm(WORM_GETTING_AIRSRIKE_DOWN_SPRITES_PATH),
                                drop_air_worm(WORM_DROPPING_AIRSRIKE_SPRITES_PATH),
                                drop_air_up_worm(WORM_DROPPING_AIRSRIKE_UP_SPRITES_PATH),
                                drop_air_down_worm(WORM_DROPPING_AIRSRIKE_DOWN_SPRITES_PATH),
                                get_tel_worm(WORM_GETTING_TELEPORT_SPRITES_PATH),
                                get_tel_up_worm(WORM_GETTING_TELEPORT_UP_SPRITES_PATH),
                                get_tel_down_worm(WORM_GETTING_TELEPORT_DOWN_SPRITES_PATH),
                                drop_tel_worm(WORM_DROPPING_TELEPORT_SPRITES_PATH),
                                drop_tel_up_worm(WORM_DROPPING_TELEPORT_UP_SPRITES_PATH),
                                drop_tel_down_worm(WORM_DROPPING_TELEPORT_DOWN_SPRITES_PATH),
                                get_thr_worm(WORM_GETTING_EMPTY_GRENADE_SPRITES_PATH),
                                get_thr_up_worm(WORM_GETTING_EMPTY_GRENADE_UP_SPRITES_PATH),
                                get_thr_down_worm(WORM_GETTING_EMPTY_GRENADE_DOWN_SPRITES_PATH),
                                drop_thr_worm(WORM_DROPPING_EMPTY_GRENADE_SPRITES_PATH),
                                drop_thr_up_worm(WORM_DROPPING_EMPTY_GRENADE_UP_SPRITES_PATH),
                                drop_thr_down_worm(WORM_DROPPING_EMPTY_GRENADE_DOWN_SPRITES_PATH),
                                get_grn_worm(WORM_GETTING_GREEN_GRENADE_SPRITES_PATH),
                                get_grn_up_worm(WORM_GETTING_GREEN_GRENADE_UP_SPRITES_PATH),
                                get_grn_down_worm(WORM_GETTING_GREEN_GRENADE_DOWN_SPRITES_PATH),
                                drop_grn_worm(WORM_DROPPING_GREEN_GRENADE_SPRITES_PATH),
                                drop_grn_up_worm(WORM_DROPPING_GREEN_GRENADE_UP_SPRITES_PATH),
                                drop_grn_down_worm(WORM_DROPPING_GREEN_GRENADE_DOWN_SPRITES_PATH),
                                get_cls_worm(WORM_GETTING_RED_GRENADE_SPRITES_PATH),
                                get_cls_up_worm(WORM_GETTING_RED_GRENADE_UP_SPRITES_PATH),
                                get_cls_down_worm(WORM_GETTING_RED_GRENADE_DOWN_SPRITES_PATH),
                                drop_cls_worm(WORM_DROPPING_RED_GRENADE_SPRITES_PATH),
                                drop_cls_up_worm(WORM_DROPPING_RED_GRENADE_UP_SPRITES_PATH),
                                drop_cls_down_worm(WORM_DROPPING_RED_GRENADE_DOWN_SPRITES_PATH),
                                get_ban_worm(WORM_GETTING_BANANA_SPRITES_PATH),
                                get_ban_up_worm(WORM_GETTING_BANANA_UP_SPRITES_PATH),
                                get_ban_down_worm(WORM_GETTING_BANANA_DOWN_SPRITES_PATH),
                                drop_ban_worm(WORM_DROPPING_BANANA_SPRITES_PATH),
                                drop_ban_up_worm(WORM_DROPPING_BANANA_UP_SPRITES_PATH),
                                drop_ban_down_worm(WORM_DROPPING_BANANA_DOWN_SPRITES_PATH),
                                get_hgr_worm(WORM_GETTING_HOLY_GRENADE_SPRITES_PATH),
                                get_hgr_up_worm(WORM_GETTING_HOLY_GRENADE_UP_SPRITES_PATH),
                                get_hgr_down_worm(WORM_GETTING_HOLY_GRENADE_DOWN_SPRITES_PATH),
                                drop_hgr_worm(WORM_DROPPING_HOLY_GRENADE_SPRITES_PATH),
                                drop_hgr_up_worm(WORM_DROPPING_HOLY_GRENADE_UP_SPRITES_PATH),
                                drop_hgr_down_worm(WORM_DROPPING_HOLY_GRENADE_DOWN_SPRITES_PATH),
                                get_dyn_worm(WORM_GETTING_DYNAMITE_SPRITES_PATH),
                                get_dyn_up_worm(WORM_GETTING_DYNAMITE_UP_SPRITES_PATH),
                                get_dyn_down_worm(WORM_GETTING_DYNAMITE_DOWN_SPRITES_PATH),
                                drop_dyn_worm(WORM_DROPPING_DYNAMITE_SPRITES_PATH),
                                drop_dyn_up_worm(WORM_DROPPING_DYNAMITE_UP_SPRITES_PATH),
                                drop_dyn_down_worm(WORM_DROPPING_DYNAMITE_DOWN_SPRITES_PATH),
                                get_bsb_worm(WORM_GETTING_BASEBALL_BAT_SPRITES_PATH),
                                get_bsb_up_worm(WORM_GETTING_BASEBALL_BAT_UP_SPRITES_PATH),
                                get_bsb_down_worm(WORM_GETTING_BASEBALL_BAT_DOWN_SPRITES_PATH),  
                                drop_bsb_worm(WORM_DROPPING_BASEBALL_BAT_SPRITES_PATH),
                                drop_bsb_up_worm(WORM_DROPPING_BASEBALL_BAT_UP_SPRITES_PATH),
                                drop_bsb_down_worm(WORM_DROPPING_BASEBALL_BAT_DOWN_SPRITES_PATH),
                                /*WORM AIMING WEAPONS*/
                                aim_baz_worm(WORM_AIMING_BAZOOKA_SPRITES_PATH),
                                aim_baz_up_worm(WORM_AIMING_BAZOOKA_UP_SPRITES_PATH),
                                aim_baz_down_worm(WORM_AIMING_BAZOOKA_DOWN_SPRITES_PATH),
                                aim_mortar_worm(WORM_AIMING_MORTAR_SPRITES_PATH),
                                aim_mortar_up_worm(WORM_AIMING_MORTAR_UP_SPRITES_PATH),
                                aim_mortar_down_worm(WORM_AIMING_MORTAR_DOWN_SPRITES_PATH),
                                aim_thr_worm(WORM_AIMING_EMPTY_GRENADE_SPRITES_PATH),
                                aim_thr_up_worm(WORM_AIMING_EMPTY_GRENADE_UP_SPRITES_PATH),
                                aim_thr_down_worm(WORM_AIMING_EMPTY_GRENADE_DOWN_SPRITES_PATH),
                                aim_grn_worm(WORM_AIMING_GREEN_GRENADE_SPRITES_PATH),
                                aim_grn_up_worm(WORM_AIMING_GREEN_GRENADE_UP_SPRITES_PATH),
                                aim_grn_down_worm(WORM_AIMING_GREEN_GRENADE_DOWN_SPRITES_PATH),
                                aim_cls_worm(WORM_AIMING_RED_GRENADE_SPRITES_PATH),
                                aim_cls_up_worm(WORM_AIMING_RED_GRENADE_UP_SPRITES_PATH),
                                aim_cls_down_worm(WORM_AIMING_RED_GRENADE_DOWN_SPRITES_PATH),
                                aim_ban_worm(WORM_AIMING_BANANA_SPRITES_PATH),
                                aim_ban_up_worm(WORM_AIMING_BANANA_UP_SPRITES_PATH),
                                aim_ban_down_worm(WORM_AIMING_BANANA_DOWN_SPRITES_PATH),
                                aim_hgr_worm(WORM_AIMING_HOLY_GRENADE_SPRITES_PATH),
                                aim_hgr_up_worm(WORM_AIMING_HOLY_GRENADE_UP_SPRITES_PATH),
                                aim_hgr_down_worm(WORM_AIMING_HOLY_GRENADE_DOWN_SPRITES_PATH),
                                aim_bsb_worm(WORM_AIMING_BASEBALL_BAT_SPRITES_PATH),
                                aim_bsb_up_worm(WORM_AIMING_BASEBALL_BAT_UP_SPRITES_PATH),
                                aim_bsb_down_worm(WORM_AIMING_BASEBALL_BAT_DOWN_SPRITES_PATH),
                                /*BEAMS*/
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
    still_baz_up_worm.SetColorKey(true, 0);
    still_baz_down_worm.SetColorKey(true, 0);
    still_mortar_worm.SetColorKey(true, 0);
    still_mortar_up_worm.SetColorKey(true, 0);
    still_mortar_down_worm.SetColorKey(true, 0);
    still_air_worm.SetColorKey(true, 0);
    still_air_up_worm.SetColorKey(true, 0);
    still_air_down_worm.SetColorKey(true, 0);
    still_tel_worm.SetColorKey(true, 0);
    still_tel_up_worm.SetColorKey(true, 0);
    still_tel_down_worm.SetColorKey(true, 0);
    still_thr_worm.SetColorKey(true, 0);
    still_thr_up_worm.SetColorKey(true, 0);
    still_thr_down_worm.SetColorKey(true, 0);
    still_grn_worm.SetColorKey(true, 0);
    still_grn_up_worm.SetColorKey(true, 0);
    still_grn_down_worm.SetColorKey(true, 0);
    still_cls_worm.SetColorKey(true, 0);
    still_cls_up_worm.SetColorKey(true, 0);
    still_cls_down_worm.SetColorKey(true, 0);
    still_ban_worm.SetColorKey(true, 0);
    still_ban_up_worm.SetColorKey(true, 0);
    still_ban_down_worm.SetColorKey(true, 0);
    still_hgr_worm.SetColorKey(true, 0);
    still_hgr_up_worm.SetColorKey(true, 0);
    still_hgr_down_worm.SetColorKey(true, 0);
    still_dyn_worm.SetColorKey(true, 0);
    still_dyn_up_worm.SetColorKey(true, 0);
    still_dyn_down_worm.SetColorKey(true, 0);
    still_bsb_worm.SetColorKey(true, 0);
    still_bsb_up_worm.SetColorKey(true, 0);
    still_bsb_down_worm.SetColorKey(true, 0);
    /*WORM CHANGING WEAPONS*/
    get_baz_worm.SetColorKey(true, 0);
    get_baz_up_worm.SetColorKey(true, 0);
    get_baz_down_worm.SetColorKey(true, 0);
    drop_baz_worm.SetColorKey(true, 0);
    drop_baz_up_worm.SetColorKey(true, 0);
    drop_baz_down_worm.SetColorKey(true, 0);
    get_mortar_worm.SetColorKey(true, 0);
    get_mortar_up_worm.SetColorKey(true, 0);
    get_mortar_down_worm.SetColorKey(true, 0);
    drop_mortar_worm.SetColorKey(true, 0);
    drop_mortar_up_worm.SetColorKey(true, 0);
    drop_mortar_down_worm.SetColorKey(true, 0);
    get_air_worm.SetColorKey(true, 0);
    get_air_up_worm.SetColorKey(true, 0);
    get_air_down_worm.SetColorKey(true, 0);
    drop_air_worm.SetColorKey(true, 0);
    drop_air_up_worm.SetColorKey(true, 0);
    drop_air_down_worm.SetColorKey(true, 0);
    get_tel_worm.SetColorKey(true, 0);
    get_tel_up_worm.SetColorKey(true, 0);
    get_tel_down_worm.SetColorKey(true, 0);
    drop_tel_worm.SetColorKey(true, 0);
    drop_tel_up_worm.SetColorKey(true, 0);
    drop_tel_down_worm.SetColorKey(true, 0);
    get_thr_worm.SetColorKey(true, 0);
    get_thr_up_worm.SetColorKey(true, 0);
    get_thr_down_worm.SetColorKey(true, 0);
    drop_thr_worm.SetColorKey(true, 0);
    drop_thr_up_worm.SetColorKey(true, 0);
    drop_thr_down_worm.SetColorKey(true, 0);
    get_grn_worm.SetColorKey(true, 0);
    get_grn_up_worm.SetColorKey(true, 0);
    get_grn_down_worm.SetColorKey(true, 0);
    drop_grn_worm.SetColorKey(true, 0);
    drop_grn_up_worm.SetColorKey(true, 0);
    drop_grn_down_worm.SetColorKey(true, 0);
    get_cls_worm.SetColorKey(true, 0);
    get_cls_up_worm.SetColorKey(true, 0);
    get_cls_down_worm.SetColorKey(true, 0);
    drop_cls_worm.SetColorKey(true, 0);
    drop_cls_up_worm.SetColorKey(true, 0);
    drop_cls_down_worm.SetColorKey(true, 0);
    get_ban_worm.SetColorKey(true, 0);
    get_ban_up_worm.SetColorKey(true, 0);
    get_ban_down_worm.SetColorKey(true, 0); 
    drop_ban_worm.SetColorKey(true, 0);
    drop_ban_up_worm.SetColorKey(true, 0);
    drop_ban_down_worm.SetColorKey(true, 0);
    get_hgr_worm.SetColorKey(true, 0);
    get_hgr_up_worm.SetColorKey(true, 0);
    get_hgr_down_worm.SetColorKey(true, 0);
    drop_hgr_worm.SetColorKey(true, 0);
    drop_hgr_up_worm.SetColorKey(true, 0);
    drop_hgr_down_worm.SetColorKey(true, 0);
    get_dyn_worm.SetColorKey(true, 0);
    get_dyn_up_worm.SetColorKey(true, 0);
    get_dyn_down_worm.SetColorKey(true, 0);
    drop_dyn_worm.SetColorKey(true, 0);
    drop_dyn_up_worm.SetColorKey(true, 0);
    drop_dyn_down_worm.SetColorKey(true, 0);
    get_bsb_worm.SetColorKey(true, 0);
    get_bsb_up_worm.SetColorKey(true, 0);
    get_bsb_down_worm.SetColorKey(true, 0);
    drop_bsb_worm.SetColorKey(true, 0);
    drop_bsb_up_worm.SetColorKey(true, 0);
    drop_bsb_down_worm.SetColorKey(true, 0);
    /*WORM AIMING WEAPONS*/
    aim_baz_worm.SetColorKey(true, 0);
    aim_baz_up_worm.SetColorKey(true, 0);
    aim_baz_down_worm.SetColorKey(true, 0);
    aim_mortar_worm.SetColorKey(true, 0);
    aim_mortar_up_worm.SetColorKey(true, 0);
    aim_mortar_down_worm.SetColorKey(true, 0);
    aim_thr_worm.SetColorKey(true, 0);
    aim_thr_up_worm.SetColorKey(true, 0);
    aim_thr_down_worm.SetColorKey(true, 0);
    aim_grn_worm.SetColorKey(true, 0);
    aim_grn_up_worm.SetColorKey(true, 0);
    aim_grn_down_worm.SetColorKey(true, 0);
    aim_cls_worm.SetColorKey(true, 0);
    aim_cls_up_worm.SetColorKey(true, 0);
    aim_cls_down_worm.SetColorKey(true, 0);
    aim_ban_worm.SetColorKey(true, 0);
    aim_ban_up_worm.SetColorKey(true, 0);
    aim_ban_down_worm.SetColorKey(true, 0);
    aim_hgr_worm.SetColorKey(true, 0);
    aim_hgr_up_worm.SetColorKey(true, 0);
    aim_hgr_down_worm.SetColorKey(true, 0);
    aim_bsb_worm.SetColorKey(true, 0);
    aim_bsb_up_worm.SetColorKey(true, 0);
    aim_bsb_down_worm.SetColorKey(true, 0);
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
