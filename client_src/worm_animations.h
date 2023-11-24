#ifndef WORM_ANIMATIONS_H
#define WORM_ANIMATIONS_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"

class WormAnimations {
public:
    WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(int state, float angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       const bool facing_left,
                       int left_offset = 0,
                       int right_offset = 0,
                       int above_offset = 0,
                       int bellow_offset = 0);
    void update_from_snapshot(int state, float angle, bool facing_left);
    void update_from_iter(int state, float angle, bool facing_left);
private:
    Animation still_0_an;
    Animation still_0_up_an;
    Animation still_0_down_an;
    Animation still_1_an;
    Animation walking_an;
    Animation walking_up_an;
    Animation walking_down_an;
    Animation backflip_an;
    Animation jump_an;
    Animation jump_up_an;
    Animation jump_down_an;
    Animation fall_an;
    Animation slide_an;
    Animation slide_up_an;
    Animation slide_down_an;
};

#endif  // WORM_ANIMATIONS_H