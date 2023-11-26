#ifndef MATCH_TEXTURES_H
#define MATCH_TEXTURES_H

#include <SDL2pp/SDL2pp.hh>

#include "constantes_cliente.h"

using namespace SDL2pp;
class MatchSurfaces {
public:    
    Surface background1;
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