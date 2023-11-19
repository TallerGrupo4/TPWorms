/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

const int FRAME_RATE = 40;
//const std::chrono::duration<double> FRAME_DURATION(1.0 / FRAME_RATE);

class SdlTexture;
class Area;

class Animation {
public:
    Animation(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal);
    ~Animation();
    void update_once();
    void update(int iter);
    void render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dest,
                SDL_RendererFlip& flipType,
                int left_offset = 0,
                int right_offset = 0,
                int above_offset = 0,
                int bellow_offset = 0);


private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    SDL2pp::Texture texture;
    /** Animation Orientation. */
    bool is_orientation_horizontal;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    //std::chrono::duration<double> elapsed;
};

#endif  //__ANIMATION_H__
