#include "worm_animations.h"

WormAnimations::WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces) :
                                still_0_an(renderer, surfaces.still_0_worm),
                                still_0_up_an(renderer, surfaces.still_0_up_worm),
                                still_0_down_an(renderer, surfaces.still_0_down_worm),
                                still_1_an(renderer, surfaces.still_1_worm),
                                walking_an(renderer, surfaces.walking_worm),
                                walking_up_an(renderer, surfaces.walking_up_worm),
                                walking_down_an(renderer, surfaces.walking_down_worm),
                                backflip_an(renderer, surfaces.backflip_worm),
                                jump_an(renderer, surfaces.jump_worm),
                                jump_up_an(renderer, surfaces.jump_up_worm),
                                jump_down_an(renderer, surfaces.jump_down_worm),
                                fall_an(renderer, surfaces.fall_worm),
                                slide_an(renderer, surfaces.slide_worm),
                                slide_up_an(renderer, surfaces.slide_up_worm),
                                slide_down_an(renderer, surfaces.slide_down_worm),
                                dead_an(renderer, surfaces.dead_worm) {

}
    
void WormAnimations::render(int state, float angle, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                    const bool facing_left,
                    int left_offset,
                    int right_offset,
                    int above_offset,
                    int bellow_offset) {       
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    switch (state) {
    case MOVING:
        walking_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case DEAD:
        dead_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset-5,
                        above_offset-12,
                        bellow_offset);
        break;
    case STILL:
        if(angle > 0) {
            if (!facing_left) {
                still_0_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                still_0_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                still_0_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                still_0_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else {
            still_0_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        }
        break;
    case CLIMBING:
        if(angle > 0) {
            if (!facing_left) {
                walking_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                walking_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                walking_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                walking_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        }
        break;
    case JUMPING:
        if(angle > 0) {
            if (!facing_left) {
                jump_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                jump_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                jump_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                jump_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else {
            jump_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        }
        break;
    case BACKFLIPPING:
        backflip_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case FALLING:
        fall_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        break;
    case SLIDING:
        if(angle > 0) {
            if (!facing_left) {
                slide_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                slide_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                slide_down_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            } else {
                slide_up_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
            }
        } else {
            slide_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        }
        break;
    default:
        break;
    }
}

void WormAnimations::update_from_snapshot(int state, float angle, bool facing_left) {
    switch (state) {
    case MOVING:
        walking_an.update_once();
        break;
    
    case CLIMBING:
        if(angle > 0) {
            if (!facing_left) {
                walking_up_an.update_once();
            } else {
                walking_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                walking_down_an.update_once();
            } else {
                walking_up_an.update_once();
            }
        }
        break;
    case JUMPING:
        if(angle > 0) {
            if (!facing_left) {
                jump_up_an.update_once();
            } else {
                jump_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                jump_down_an.update_once();
            } else {
                jump_up_an.update_once();
            }
        } else {
            jump_an.update_once();
        }
        break;
    case BACKFLIPPING:
        backflip_an.update_once();
        break;
    case FALLING:
        walking_an.update_once();
        break;
    case SLIDING:
        if(angle > 0) {
            if (!facing_left) {
                slide_up_an.update_once();
            } else {
                slide_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                slide_down_an.update_once();
            } else {
                slide_up_an.update_once();
            }
        } else {
            slide_an.update_once();
        }
        break;
    default:
        break;
    }
}

void WormAnimations::update_from_iter(int state, float angle, bool facing_left) {
    switch (state) {
    case STILL:
        if(angle > 0) {
            if (!facing_left) {
                still_0_up_an.update_once();
            } else {
                still_0_down_an.update_once();
            }
        } else if (angle < 0) {
            if (!facing_left) {
                still_0_down_an.update_once();
            } else {
                still_0_up_an.update_once();
            }
        } else {
            still_0_an.update_once();
        }
        break;
    case DEAD:
        dead_an.update_once();
        break;
    default:
        break;
    }
}