#include "AnimationScroll.h"

AnimationScroll::AnimationScroll(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration, bool one_loop, bool is_orientation_horizontal): Animation(renderer, surface, loop_duration, one_loop, is_orientation_horizontal) {
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
    this->actual_time_between_frames = this->time_between_frames;
}

AnimationScroll::~AnimationScroll() {}
