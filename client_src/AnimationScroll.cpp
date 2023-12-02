#include "AnimationScroll.h"

AnimationScroll::AnimationScroll(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal): Animation(renderer, surface, 0, false, false, is_orientation_horizontal) {
    currentFrame = 16;
}

void AnimationScroll::update_once_up() {
    if ((this->currentFrame) != 0) {
        this->currentFrame -= 1;
    }
}

void AnimationScroll::update_once_down() {
    if ((this->currentFrame+1) != this->numFrames) {
        this->currentFrame += 1;
    }
}

void AnimationScroll::reset() {
    this->currentFrame = 16;
}

AnimationScroll::~AnimationScroll() {}
