/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

class SdlTexture;
class Area;

// Class that represents an animation
class Animation {
public:
    /**
     * @brief Construct a new Animation object
     * @param renderer Renderer of the match
     * @param surface Surface of the animation
     * @param loop_duration_miliseconds Duration of the animation in miliseconds
     * @param one_loop If the animation is played once
     * @param loop_reversed If the animation is looped in reverse
     * @param is_orientation_horizontal If the animation is in horizontal format
     */
    Animation(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration_miliseconds,
              bool one_loop = false, bool loop_reversed = false,
              bool is_orientation_horizontal = false);
    ~Animation();
    bool update_once();
    virtual void update_once_up() { return; }
    virtual void update_once_down() { return; }
    virtual void update_with_angle(int angle) { return; }
    /**
     * @brief Renders the animation
     * @param renderer Renderer of the match
     * @param dest Destination rectangle of the animation
     * @param flipType Flip type of the animation
     * @param left_offset Offset of the left side of the animation
     * @param right_offset Offset of the right side of the animation
     * @param above_offset Offset of the top side of the animation
     * @param bellow_offset Offset of the bottom side of the animation
     */
    void render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dest, SDL_RendererFlip& flipType,
                int left_offset = 0, int right_offset = 0, int above_offset = 0,
                int bellow_offset = 0);
    virtual void reset();
    int get_frame_size();

protected:
    bool advanceFrame();
    /** SDL texture of the raw image. */
    SDL2pp::Texture texture;
    /** Animation Orientation. */
    bool is_orientation_horizontal;

    bool one_loop;
    bool loop_reversed;
    bool reverse;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time needed to update. */
    uint time_between_frames;
    /** Time elapsed since last update. */
    uint actual_time_between_frames;
};

#endif  //__ANIMATION_H__
