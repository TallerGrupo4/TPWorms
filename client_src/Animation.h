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

class Animation {
public:
    Animation(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration, bool one_loop = false, bool is_orientation_horizontal = false);
    ~Animation();
    bool update_once();
    virtual void update_once_up() {return;}
    virtual void update_once_down() {return;}
    virtual void update_with_angle(int angle) {return;}
    void render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dest,
                SDL_RendererFlip& flipType,
                int left_offset = 0,
                int right_offset = 0,
                int above_offset = 0,
                int bellow_offset = 0);
    void reset();
    int get_frame_size();

protected:
    bool advanceFrame();
    /** SDL texture of the raw image. */
    SDL2pp::Texture texture;
    /** Animation Orientation. */
    bool is_orientation_horizontal;

    bool one_loop;
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

