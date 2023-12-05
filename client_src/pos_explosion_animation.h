#ifndef POS_EXPLOSION_AN_H
#define POS_EXPLOSION_AN_H

#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "client_constants.h"
#include "surfaces.h"

// Class that holds the position, explosion_size and the animation. It is only used in the
// EffectsAnimations class
class PosExplosionAndAnimation {
private:
    int x;
    int y;
    int explosion_size;
    Animation an;

public:
    PosExplosionAndAnimation(int x, int y, SDL2pp::Renderer& renderer, SDL2pp::Surface& surface,
                             uint seconds_for_an, bool an_is_looped, int explosion_size = 0);
    int get_x();
    int get_y();
    int get_explosion_size();
    Animation& get_an();
};

#endif  // POS_EXPLOSION_AN_H
