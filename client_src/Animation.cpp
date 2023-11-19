/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include "Animation.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include <SDL2pp/SDL2pp.hh>

Animation::Animation(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal) :
        texture(SDL2pp::Texture(renderer,surface)),
        is_orientation_horizontal(is_orientation_horizontal),
        currentFrame(0),
        numFrames(this->is_orientation_horizontal ?
                          (this->texture.GetWidth() / this->texture.GetHeight()) :
                          (this->texture.GetHeight() / this->texture.GetWidth())),
        size(this->is_orientation_horizontal ? this->texture.GetHeight() :
                                               this->texture.GetWidth()) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

void Animation::update_once() {
    this->advanceFrame();
}

void Animation::update(int iter) {
    for (int i = 0; i < iter; i++) {
        this->advanceFrame();
    }
    
    // this->elapsed += dt;
    // /* checks if the frame should be updated based on the time elapsed since the last update */
    // while (this->elapsed > FRAME_DURATION) {
    //     this->advanceFrame();
    //     this->elapsed -= FRAME_DURATION;
    // }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       SDL_RendererFlip& flipType,
                       int left_offset,
                       int right_offset,
                       int above_offset,
                       int bellow_offset) {
    renderer.Copy(
            this->texture,
            (this->is_orientation_horizontal ?
                     SDL2pp::Rect(left_offset + this->size * this->currentFrame, above_offset, this->size - left_offset - right_offset, this->size - above_offset - bellow_offset) :
                     SDL2pp::Rect(left_offset, this->size * this->currentFrame + above_offset, this->size - left_offset - right_offset, this->size - above_offset - bellow_offset)),
            dst,
            0.0,              // don't rotate
            SDL2pp::NullOpt,  // rotation center - not needed
            flipType);
}

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames;
}
