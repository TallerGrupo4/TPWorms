/*
 * Inspired by the work from Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include "Animation.h"

Animation::Animation(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration_seconds, bool one_loop, bool loop_reversed, bool is_orientation_horizontal) :
        texture(SDL2pp::Texture(renderer,surface)),
        is_orientation_horizontal(is_orientation_horizontal),
        one_loop(one_loop),
        loop_reversed(loop_reversed),
        reverse(false),
        currentFrame(0),
        numFrames(this->is_orientation_horizontal ?
                          (this->texture.GetWidth() / this->texture.GetHeight()) :
                          (this->texture.GetHeight() / this->texture.GetWidth())),
        size(this->is_orientation_horizontal ? this->texture.GetHeight() :
                                               this->texture.GetWidth()),
        time_between_frames(std::round(static_cast<float>(loop_duration_seconds * FPS) / numFrames)),
        actual_time_between_frames(time_between_frames) {    
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

bool Animation::update_once() {
    return this->advanceFrame();
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

bool Animation::advanceFrame() {
    if(this->one_loop) {
        if (((this->currentFrame+1) == this->numFrames) and (this->actual_time_between_frames == 0)) {
            return false;
        }
    }
    if (this->actual_time_between_frames != 0) {
        this->actual_time_between_frames -= 1;
    } else {
        if (this->loop_reversed) {
            if (this->reverse) {
                this->currentFrame -= 1;
                if (this->currentFrame < 0) {
                    this->currentFrame = 1;
                    this->reverse = false;
                }
            } else {
                this->currentFrame += 1;
                if (this->currentFrame == this->numFrames-1) {
                    this->currentFrame = this->numFrames-2;
                    this->reverse = true;
                }
            }
        } else {
            this->currentFrame += 1;
            this->currentFrame = this->currentFrame % this->numFrames;
        }
        this->actual_time_between_frames = this->time_between_frames;
        // if (this->reverse) {
        //     this->currentFrame -= 1;
        //     if (this->currentFrame < 0) {
        //         this->currentFrame = 0;
        //         this->reverse = false;
        //     }
        // } else {
        //     this->currentFrame += 1;
        //     if (this->currentFrame == this->numFrames) {
        //         this->currentFrame = this->numFrames - 1;
        //         this->reverse = true;
        //     }
        // }
        // this->actual_time_between_frames = this->time_between_frames;
    }
    return true;

    // if(this->one_loop) {
    //     if (((this->currentFrame+1) == this->numFrames) and (this->actual_time_between_frames == 0)) {
    //         return false;
    //     }
    // }
    // if (this->actual_time_between_frames != 0) {
    //     this->actual_time_between_frames -= 1;
    // } else {
    //     this->currentFrame += 1;
    //     this->currentFrame = this->currentFrame % this->numFrames;
    //     this->actual_time_between_frames = this->time_between_frames;
    // }
    // return true;
}

void Animation::reset() {
    this->currentFrame = 0;
    this->actual_time_between_frames = this->time_between_frames;
}

int Animation::get_frame_size() {
    return this->size;
}
