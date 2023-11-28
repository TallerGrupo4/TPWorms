#include "Animation.h"

#ifndef __ANIMATIONSCROLL_H__
#define __ANIMATIONSCROLL_H__

class AnimationScroll : public Animation {
public:
    void update_once_up() override;
    void update_once_down() override;
    AnimationScroll(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint loop_duration, bool one_loop = false, bool is_orientation_horizontal = false);
    ~AnimationScroll();
};

#endif  //__ANIMATIONSCROLL_H__
