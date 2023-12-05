#include "pos_explosion_animation.h"

PosExplosionAndAnimation::PosExplosionAndAnimation(int x, int y, SDL2pp::Renderer& renderer, SDL2pp::Surface& surface,
                    uint seconds_for_an, bool an_is_looped, int explosion_size):
            x(x),
            y(y),
            explosion_size(explosion_size),
            an(renderer, surface, seconds_for_an, an_is_looped) {}

int PosExplosionAndAnimation::get_x() { return x; }

int PosExplosionAndAnimation::get_y() { return y; }

int PosExplosionAndAnimation::get_explosion_size() { return explosion_size; }

Animation& PosExplosionAndAnimation::get_an() { return an; }
