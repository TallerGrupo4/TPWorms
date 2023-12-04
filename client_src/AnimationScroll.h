#include "Animation.h"

#ifndef __ANIMATIONSCROLL_H__
#define __ANIMATIONSCROLL_H__

class AnimationScroll : public Animation {
public:
    void update_with_angle(int angle);
    AnimationScroll(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal = false);
    ~AnimationScroll();
};

#endif  //__ANIMATIONSCROLL_H__
