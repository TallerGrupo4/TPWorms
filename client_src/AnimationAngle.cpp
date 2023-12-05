#include "AnimationAngle.h"

AnimationAngle::AnimationAngle(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface,
                               bool is_orientation_horizontal):
        Animation(renderer, surface, 0, false, false, is_orientation_horizontal) {
    currentFrame = 8;
}

void AnimationAngle::update_with_angle(int angle) {
    int last_frame = this->numFrames - 1;
    if (angle < 180 and angle > 174.375f) {
        this->currentFrame = last_frame - 7;
    } else if (angle < 174.375f and angle > 163.125f) {
        this->currentFrame = last_frame - 6;
    } else if (angle < 163.125f and angle > 151.875f) {
        this->currentFrame = last_frame - 5;
    } else if (angle < 151.875f and angle > 140.625f) {
        this->currentFrame = last_frame - 4;
    } else if (angle < 140.625f and angle > 129.375f) {
        this->currentFrame = last_frame - 3;
    } else if (angle < 129.375f and angle > 118.125f) {
        this->currentFrame = last_frame - 2;
    } else if (angle < 118.125f and angle > 106.875f) {
        this->currentFrame = last_frame - 1;
    } else if (angle < 106.875f and angle > 95.625f) {
        this->currentFrame = last_frame;
    } else if (angle < 95.625f and angle > 84.375f) {
        this->currentFrame = 0;
    } else if (angle < 84.375f and angle > 73.125f) {
        this->currentFrame = 1;
    } else if (angle < 73.125f and angle > 61.875f) {
        this->currentFrame = 2;
    } else if (angle < 61.875f and angle > 50.625f) {
        this->currentFrame = 3;
    } else if (angle < 50.625f and angle > 39.375f) {
        this->currentFrame = 4;
    } else if (angle < 39.375f and angle > 28.125f) {
        this->currentFrame = 5;
    } else if (angle < 28.125f and angle > 16.875f) {
        this->currentFrame = 6;
    } else if (angle < 16.875f and angle > 5.625f) {
        this->currentFrame = 7;
    } else if (angle < 5.625f and angle > -5.625f) {
        this->currentFrame = 8;
    } else if (angle < -5.625f and angle > -16.875f) {
        this->currentFrame = 9;
    } else if (angle < -16.875f and angle > -28.125f) {
        this->currentFrame = 10;
    } else if (angle < -28.125f and angle > -39.375f) {
        this->currentFrame = 11;
    } else if (angle < -39.375f and angle > -50.625f) {
        this->currentFrame = 12;
    } else if (angle < -50.625f and angle > -61.875f) {
        this->currentFrame = 13;
    } else if (angle < -61.875f and angle > -73.125f) {
        this->currentFrame = 14;
    } else if (angle < -73.125f and angle > -84.375f) {
        this->currentFrame = 15;
    } else if (angle < -84.375f and angle > -95.625f) {
        this->currentFrame = 16;
    } else if (angle < -95.625f and angle > -106.875f) {
        this->currentFrame = 17;
    } else if (angle < -106.875f and angle > -118.125f) {
        this->currentFrame = 18;
    } else if (angle < -118.125f and angle > -129.375f) {
        this->currentFrame = 19;
    } else if (angle < -129.375f and angle > -140.625f) {
        this->currentFrame = 20;
    } else if (angle < -140.625f and angle > -151.875f) {
        this->currentFrame = 21;
    } else if (angle < -151.875f and angle > -163.125f) {
        this->currentFrame = 22;
    } else if (angle < -163.125f and angle > -174.375f) {
        this->currentFrame = 23;
    } else if (angle < -174.375f and angle > -180) {
        this->currentFrame = 24;
    }
}

AnimationAngle::~AnimationAngle() {}
