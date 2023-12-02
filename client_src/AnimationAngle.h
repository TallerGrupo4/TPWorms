#include "Animation.h"

#ifndef __ANIMATIONANGLE_H__
#define __ANIMATIONANGLE_H__

class AnimationAngle : public Animation {
public:
    void update_with_angle(int angle) override;
    AnimationAngle(SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, bool is_orientation_horizontal = false);
    ~AnimationAngle();
};

#endif  //__ANIMATIONANGLE_H__