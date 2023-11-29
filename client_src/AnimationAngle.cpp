#include "AnimationAngle.h"

AnimationAngle::AnimationAngle(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration, bool one_loop, bool is_orientation_horizontal): Animation(renderer, surface, loop_duration, one_loop, is_orientation_horizontal) {
    currentFrame = 8;
}

void AnimationAngle::update_with_angle(int angle) {
    if(angle < 90 and angle > 84.375f) {
        this->currentFrame = 0;
    } else if (angle < 84.375f and angle > 78.75f) {
        this->currentFrame = 1;
    } else if (angle < 78.75f and angle > 73.125f) {
        this->currentFrame = 1;
    } else if (angle < 73.125f and angle > 67.5f) {
        this->currentFrame = 2;
    } else if (angle < 67.5f and angle > 61.875f) {
        this->currentFrame = 2;
    } else if (angle < 61.875f and angle > 56.25f) {
        this->currentFrame = 3;
    } else if (angle < 56.25f and angle > 50.625f) {
        this->currentFrame = 3;
    } else if (angle < 50.625f and angle > 45) {
        this->currentFrame = 4;
    } else if (angle < 45 and angle > 39.375f) {
        this->currentFrame = 4;
    } else if (angle < 39.375f and angle > 33.75f) {
        this->currentFrame = 5;
    } else if (angle < 33.75f and angle > 28.125f) {
        this->currentFrame = 5;
    } else if (angle < 28.125f and angle > 22.5f) {
        this->currentFrame = 6;
    } else if (angle < 22.5f and angle > 16.875f) {
        this->currentFrame = 6;
    } else if (angle < 16.875f and angle > 11.25f) {
        this->currentFrame = 7;
    } else if (angle < 11.25f and angle > 5.625f) {
        this->currentFrame = 7;
    } else if (angle < 5.625f and angle > 0) {
        this->currentFrame = 8;
    } else if (angle < 0 and angle > -5.625f) {
        this->currentFrame = 8;
    } else if (angle < -5.625f and angle > -11.25f) {
        this->currentFrame = 9;
    } else if (angle < -11.25f and angle > -16.875f) {
        this->currentFrame = 9;
    } else if (angle < -16.875f and angle > -22.5f) {
        this->currentFrame = 10;
    } else if (angle < -22.5f and angle > -28.125f) {
        this->currentFrame = 10;
    } else if (angle < -28.125f and angle > -33.75f) {
        this->currentFrame = 11;
    } else if (angle < -33.75f and angle > -39.375f) {
        this->currentFrame = 11;
    } else if (angle < -39.375f and angle > -45) {
        this->currentFrame = 12;
    } else if (angle < -45 and angle > -50.625f) {
        this->currentFrame = 12;
    } else if (angle < -50.625f and angle > -56.25f) {
        this->currentFrame = 13;
    } else if (angle < -56.25f and angle > -61.875f) {
        this->currentFrame = 13;
    } else if (angle < -61.875f and angle > -67.5f) {
        this->currentFrame = 14;
    } else if (angle < -67.5f and angle > -73.125f) {
        this->currentFrame = 14;
    } else if (angle < -73.125f and angle > -78.75f) {
        this->currentFrame = 15;
    } else if (angle < -78.75f and angle > -84.375f) {
        this->currentFrame = 15;
    } else if (angle < -84.375f and angle > -90) {
        this->currentFrame = 16;
    }
}

AnimationAngle::~AnimationAngle() {}