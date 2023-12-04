#include "AnimationScroll.h"

AnimationScroll::AnimationScroll(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal): Animation(renderer, surface, 0, false, false, is_orientation_horizontal) {
    currentFrame = 15;
}

void AnimationScroll::update_with_angle(int angle) {
    //int last_frame = this->numFrames-1;
    if (angle < -87) {
        this->currentFrame = 0;
    } else if (angle > -87 and angle < -81) {
        this->currentFrame = 1;
    } else if (angle > -81 and angle < -75) {
        this->currentFrame = 2;
    } else if (angle > -75 and angle < -69) {
        this->currentFrame = 3;
    } else if (angle > -69 and angle < -63) {
        this->currentFrame = 4;
    } else if (angle > -63 and angle < -57) {
        this->currentFrame = 5;
    } else if (angle > -57 and angle < -51) {
        this->currentFrame = 6;
    } else if(angle > -51 and angle < -45) {
        this->currentFrame = 7;
    } else if (angle > -45 and angle < -39) {
        this->currentFrame = 8;
    } else if (angle > -39 and angle < -33) {
        this->currentFrame = 9;
    } else if (angle > -33 and angle < -27) {
        this->currentFrame = 10;
    } else if (angle > -27 and angle < -21) {
        this->currentFrame = 11;
    } else if (angle > -21 and angle < -15) {
        this->currentFrame = 12;
    } else if (angle > -15 and angle < -9) {
        this->currentFrame = 13;
    } else if (angle > -9 and angle < -3) {
        this->currentFrame = 14;
    } else if (angle > -3 and angle < 2.8125f) {
        this->currentFrame = 15;
    } else if (angle > 2.8125f and angle < 8.4375f) {
        this->currentFrame = 16;
    } else if (angle > 8.4375f and angle < 14.0625f) {
        this->currentFrame = 17;
    } else if (angle > 14.0625f and angle < 19.6875f) {
        this->currentFrame = 18;
    } else if (angle > 19.6875f and angle < 25.3125f) {
        this->currentFrame = 19;
    } else if (angle > 25.3125f and angle < 30.9375f) {
        this->currentFrame = 20;
    } else if (angle > 30.9375f and angle < 36.5625f) {
        this->currentFrame = 21;
    } else if (angle > 36.5625f and angle < 42.1875f) {
        this->currentFrame = 22;
    } else if (angle > 42.1875f and angle < 47.8125f) {
        this->currentFrame = 23;
    } else if (angle > 47.8125f and angle < 53.4375f) {
        this->currentFrame = 24;
    } else if (angle > 53.4375f and angle < 59.0625f) {
        this->currentFrame = 25;
    } else if (angle > 59.0625f and angle < 64.6875f) {
        this->currentFrame = 26;
    } else if (angle > 64.6875f and angle < 70.3125f) {
        this->currentFrame = 27;
    } else if (angle > 70.3125f and angle < 75.9375f) {
        this->currentFrame = 28;
    } else if (angle > 75.9375f and angle < 81.5625f) {
        this->currentFrame = 29;
    } else if (angle > 81.5625f and angle < 87.1875f) {
        this->currentFrame = 30;
    } else if (angle > 87.1875f) {
        this->currentFrame = 31;
    }
}

AnimationScroll::~AnimationScroll() {}
