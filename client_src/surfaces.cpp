#include "surfaces.h"

using namespace SDL2pp;

MatchSurfaces::MatchSurfaces() : background1(BACKGROUND1_PATH),
                                 walking_worm(WORM_WALK_SPRITES_PATH),
                                 walking_up_worm(WORM_WALK_UP_SPRITES_PATH),
                                 walking_down_worm(WORM_WALK_DOWN_SPRITES_PATH),
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
    walking_worm.SetColorKey(true, 0);
    walking_up_worm.SetColorKey(true, 0);
    walking_down_worm.SetColorKey(true, 0);
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
