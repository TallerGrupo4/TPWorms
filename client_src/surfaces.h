#ifndef MATCH_TEXTURES_H
#define MATCH_TEXTURES_H

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

using namespace SDL2pp;
class MatchSurfaces {
public:    
    /*BACKGROUND*/
    Surface background1;
    /*CROSSHAIR/MARKER*/
    Surface crosshair_blue;
    Surface crosshair_red;
    Surface crosshair_green;
    Surface crosshair_yellow;
    Surface crossharir_purple;
    Surface marker_blue;
    Surface marker_red;
    Surface marker_green;
    Surface marker_yellow;
    Surface marker_purple;
    /*WORM MOVEMENTS*/
    Surface still_0_worm;
    Surface still_0_up_worm;
    Surface still_0_down_worm;
    Surface still_1_worm;
    Surface walking_worm;
    Surface walking_up_worm;
    Surface walking_down_worm;
    Surface backflip_worm;
    Surface jump_worm;
    Surface jump_up_worm;
    Surface jump_down_worm;
    Surface fall_worm;
    Surface slide_worm;
    Surface slide_up_worm;
    Surface slide_down_worm;
    Surface dead_worm;
    /*WORM STILL STANCE WEAPONS*/
    Surface still_baz_worm;
    Surface still_baz_up_worm;
    Surface still_baz_down_worm;
    Surface still_mortar_worm;
    Surface still_mortar_up_worm;
    Surface still_mortar_down_worm;
    Surface still_air_worm;
    Surface still_air_up_worm;
    Surface still_air_down_worm;
    Surface still_tel_worm;
    Surface still_tel_up_worm;
    Surface still_tel_down_worm;
    Surface still_thr_worm;
    Surface still_thr_up_worm;
    Surface still_thr_down_worm;
    Surface still_grn_worm;
    Surface still_grn_up_worm;
    Surface still_grn_down_worm;
    Surface still_cls_worm;
    Surface still_cls_up_worm;
    Surface still_cls_down_worm;
    Surface still_ban_worm;
    Surface still_ban_up_worm;
    Surface still_ban_down_worm;
    Surface still_hgr_worm;
    Surface still_hgr_up_worm;
    Surface still_hgr_down_worm;
    Surface still_dyn_worm;
    Surface still_dyn_up_worm;
    Surface still_dyn_down_worm;
    Surface still_bsb_worm;
    Surface still_bsb_up_worm;
    Surface still_bsb_down_worm;
    /*WORM CHANGING WEAPONS*/
    Surface get_baz_worm;
    Surface get_baz_up_worm;
    Surface get_baz_down_worm;
    Surface drop_baz_worm;
    Surface drop_baz_up_worm;
    Surface drop_baz_down_worm;
    Surface get_mortar_worm;
    Surface get_mortar_up_worm;
    Surface get_mortar_down_worm;
    Surface drop_mortar_worm;
    Surface drop_mortar_up_worm;
    Surface drop_mortar_down_worm;
    Surface get_air_worm;
    Surface get_air_up_worm;
    Surface get_air_down_worm;
    Surface drop_air_worm;
    Surface drop_air_up_worm;
    Surface drop_air_down_worm;
    Surface get_tel_worm;
    Surface get_tel_up_worm;
    Surface get_tel_down_worm;
    Surface drop_tel_worm;
    Surface drop_tel_up_worm;
    Surface drop_tel_down_worm;
    Surface get_thr_worm;
    Surface get_thr_up_worm;
    Surface get_thr_down_worm;
    Surface drop_thr_worm;
    Surface drop_thr_up_worm;
    Surface drop_thr_down_worm;
    Surface get_grn_worm;
    Surface get_grn_up_worm;
    Surface get_grn_down_worm;
    Surface drop_grn_worm;
    Surface drop_grn_up_worm;
    Surface drop_grn_down_worm;
    Surface get_cls_worm;
    Surface get_cls_up_worm;
    Surface get_cls_down_worm;
    Surface drop_cls_worm;
    Surface drop_cls_up_worm;
    Surface drop_cls_down_worm;
    Surface get_ban_worm;
    Surface get_ban_up_worm;
    Surface get_ban_down_worm;
    Surface drop_ban_worm;
    Surface drop_ban_up_worm;
    Surface drop_ban_down_worm;
    Surface get_hgr_worm;
    Surface get_hgr_up_worm;
    Surface get_hgr_down_worm;
    Surface drop_hgr_worm;
    Surface drop_hgr_up_worm;
    Surface drop_hgr_down_worm;
    Surface get_dyn_worm;
    Surface get_dyn_up_worm;
    Surface get_dyn_down_worm;
    Surface drop_dyn_worm;
    Surface drop_dyn_up_worm;
    Surface drop_dyn_down_worm;
    Surface get_bsb_worm;
    Surface get_bsb_up_worm;
    Surface get_bsb_down_worm;  
    Surface drop_bsb_worm;
    Surface drop_bsb_up_worm;
    Surface drop_bsb_down_worm;
    /*WORM AIMING WEAPONS*/
    Surface aim_baz_worm;
    Surface aim_baz_up_worm;
    Surface aim_baz_down_worm;
    Surface aim_mortar_worm;
    Surface aim_mortar_up_worm;
    Surface aim_mortar_down_worm;
    Surface aim_thr_worm;
    Surface aim_thr_up_worm;
    Surface aim_thr_down_worm;
    Surface aim_grn_worm;
    Surface aim_grn_up_worm;
    Surface aim_grn_down_worm;
    Surface aim_cls_worm;
    Surface aim_cls_up_worm;
    Surface aim_cls_down_worm;
    Surface aim_ban_worm;
    Surface aim_ban_up_worm;
    Surface aim_ban_down_worm;
    Surface aim_hgr_worm;
    Surface aim_hgr_up_worm;
    Surface aim_hgr_down_worm;
    Surface aim_bsb_worm;
    Surface aim_bsb_up_worm;
    Surface aim_bsb_down_worm;
    /*PROJECTILES*/
    Surface bazooka_missile;
    Surface mortar_round;
    Surface air_missile;
    Surface banana;
    Surface cluster_bomb;
    Surface cluster_bomb_fragments;
    Surface dynamite;
    Surface grenade;
    Surface holy_grenade;
    /*EFFECTS (EXPLOSIONS/SMOKE/HITS)*/
    Surface big_circle_explosion;
    Surface small_circle_explosion;
    Surface big_ring_explosion;
    Surface small_ring_explosion;
    Surface missile_exhaust;
    Surface baseball_bat_hit;
    Surface worm_hit;
    /*BEAMS*/
    Surface large_beam_vertical;
    Surface large_beam_65;
    Surface large_beam_45;
    Surface large_beam_25;
    Surface large_beam_horizontal;
    Surface large_beam_m_25;
    Surface large_beam_m_45;
    Surface large_beam_m_65;
    Surface large_beam_vertical_flipped;
    Surface short_beam_vertical;
    Surface short_beam_65;
    Surface short_beam_45;
    Surface short_beam_25;
    Surface short_beam_horizontal;
    Surface short_beam_m_25;
    Surface short_beam_m_45;
    Surface short_beam_m_65;
    Surface short_beam_vertical_flipped;
    
    explicit MatchSurfaces();
};
#endif  // MATCH_TEXTURES_H