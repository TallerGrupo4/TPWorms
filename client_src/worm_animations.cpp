#include "worm_animations.h"

WormAnimations::WormAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces) :
                                still_0_an(renderer, surfaces.still_0_worm, SECS_FOR_STILL_SPRITES),
                                still_0_up_an(renderer, surfaces.still_0_up_worm, SECS_FOR_STILL_SPRITES),
                                still_0_down_an(renderer, surfaces.still_0_down_worm, SECS_FOR_STILL_SPRITES),
                                still_1_an(renderer, surfaces.still_1_worm, SECS_FOR_STILL_1_SPRITES),
                                walking_an(renderer, surfaces.walking_worm, SECS_FOR_WALKING_SPRITES),
                                walking_up_an(renderer, surfaces.walking_up_worm, SECS_FOR_WALKING_SPRITES),
                                walking_down_an(renderer, surfaces.walking_down_worm, SECS_FOR_WALKING_SPRITES),
                                backflip_an(renderer, surfaces.backflip_worm, SECS_FOR_BACKFLIP_SPRITES),
                                jump_an(renderer, surfaces.jump_worm, SECS_FOR_JUMP_SPRITES, true),
                                jump_up_an(renderer, surfaces.jump_up_worm, SECS_FOR_JUMP_SPRITES, true),
                                jump_down_an(renderer, surfaces.jump_down_worm, SECS_FOR_JUMP_SPRITES, true),
                                fall_an(renderer, surfaces.fall_worm, SECS_FOR_FALL_SPRITES),
                                slide_an(renderer, surfaces.slide_worm, SECS_FOR_SLIDE_SPRITES),
                                slide_up_an(renderer, surfaces.slide_up_worm, SECS_FOR_SLIDE_SPRITES),
                                slide_down_an(renderer, surfaces.slide_down_worm, SECS_FOR_SLIDE_SPRITES),
                                dead_an(renderer, surfaces.dead_worm, SECS_FOR_DEAD_SPRITES),
                                still_baz_an(renderer, surfaces.still_baz_worm, SECS_FOR_STILL_SPRITES),
                                get_baz_an(renderer, surfaces.get_baz_worm, SECS_FOR_STILL_SPRITES, true),
                                get_baz_up_an(renderer, surfaces.get_baz_up_worm, SECS_FOR_STILL_SPRITES, true),
                                get_baz_down_an(renderer, surfaces.get_baz_down_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_an(renderer, surfaces.drop_baz_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_up_an(renderer, surfaces.drop_baz_up_worm, SECS_FOR_STILL_SPRITES, true),
                                drop_baz_down_an(renderer, surfaces.drop_baz_down_worm, SECS_FOR_STILL_SPRITES, true),
                                aim_baz_an(renderer, surfaces.aim_baz_worm, SECS_FOR_STILL_SPRITES),
                                aim_baz_up_an(renderer, surfaces.aim_baz_up_worm, SECS_FOR_STILL_SPRITES),
                                aim_baz_down_an(renderer, surfaces.aim_baz_down_worm, SECS_FOR_STILL_SPRITES) {

}
    
void WormAnimations::render_angle_dependent_an(Animation& up_an, Animation& down_an,
                                               const int angle, const bool facing_left,
                                               SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                                               SDL_RendererFlip flip,
                                               int left_offset,
                                               int right_offset,
                                               int above_offset,
                                               int bellow_offset) {
    if(angle > 0) {
        if (!facing_left) {
            up_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        } else {
            down_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        }
    } else if (angle < 0) {
        if (!facing_left) {
            down_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        } else {
            up_an.render(renderer, dst,
                    flip,
                    left_offset,
                    right_offset,
                    above_offset,
                    bellow_offset);
        }
    }
}

void WormAnimations::render(int state, int angle, TOOLS weapon, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                    const bool facing_left,
                    int left_offset,
                    int right_offset,
                    int above_offset,
                    int bellow_offset) {       
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if(!lingering_animations.empty()) {
        lingering_animations.front().get().render(renderer, dst,
                                            flip,
                                            left_offset,
                                            right_offset,
                                            above_offset,
                                            bellow_offset);
        return;
    }
    
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
        switch (weapon) {
        case BAZOOKA:
            if(angle == 0) {
                still_baz_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_0_up_an, still_0_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case MORTAR:
            // lingering_animations.push_back();
            break;
        case GREEN_GRENADE:
            // lingering_animations.push_back();
            break;
        case HOLY_GRENADE:
            // lingering_animations.push_back();
            break;
        case DYNAMITE:
            // lingering_animations.push_back();
            break;
        case BASEBALL_BAT:
            // lingering_animations.push_back();
            break;
        case RED_GRENADE:
            // lingering_animations.push_back();
            break;
        case BANANA:
            // lingering_animations.push_back();
            break;
        case AIRSTRIKE:
            // lingering_animations.push_back();
            break;
        case TELEPORTATION:
            // lingering_animations.push_back();
            break;
        case NO_TOOL:
            if(angle == 0) {
                still_0_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(still_0_up_an, still_0_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        }
        break;
    case CLIMBING:
        render_angle_dependent_an(walking_up_an, walking_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        break;
    case JUMPING:
        if(angle == 0) {
            jump_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        } else {
            render_angle_dependent_an(jump_up_an, jump_down_an,
                                    angle, facing_left,
                                    renderer, dst,
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
        if(angle == 0) {
            slide_an.render(renderer, dst,
                        flip,
                        left_offset,
                        right_offset,
                        above_offset,
                        bellow_offset);
        } else {
            render_angle_dependent_an(slide_up_an, slide_down_an,
                                    angle, facing_left,
                                    renderer, dst,
                                    flip,
                                    left_offset,
                                    right_offset,
                                    above_offset,
                                    bellow_offset);
        }
        break;
    case AIMING:
        switch (weapon) {
        case BAZOOKA:
            if(angle == 0) {
                aim_baz_an.render(renderer, dst,
                            flip,
                            left_offset,
                            right_offset,
                            above_offset,
                            bellow_offset);
            } else {
                render_angle_dependent_an(aim_baz_up_an, aim_baz_down_an,
                                        angle, facing_left,
                                        renderer, dst,
                                        flip,
                                        left_offset,
                                        right_offset,
                                        above_offset,
                                        bellow_offset);
            }
            break;
        case MORTAR:
            // lingering_animations.push_back();
            break;
        case GREEN_GRENADE:
            // lingering_animations.push_back();
            break;
        case HOLY_GRENADE:
            // lingering_animations.push_back();
            break;
        case DYNAMITE:
            // lingering_animations.push_back();
            break;
        case BASEBALL_BAT:
            // lingering_animations.push_back();
            break;
        case RED_GRENADE:
            // lingering_animations.push_back();
            break;
        case BANANA:
            // lingering_animations.push_back();
            break;
        case AIRSTRIKE:
            // lingering_animations.push_back();
            break;
        case TELEPORTATION:
            // lingering_animations.push_back();
            break;
        case NO_TOOL:
            break;
        }
        break;
    default:
        break;
    }
}

void WormAnimations::update_from_snapshot(int state, int angle, bool facing_left, int old_aiming_angle, int new_aiming_angle) {
    if((is_action_state(state)) and (!lingering_animations.empty())) {
        for (auto& an : lingering_animations) {
            an.get().reset();
        }
        lingering_animations.clear();
    }
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
    case AIMING:
        std::cout << "ENTRE al AIMING del update from snapshot, new_aiming_angle: " << new_aiming_angle << " old_aiming_angle: " << old_aiming_angle << std::endl;
        if(angle > 0) {
            if (!facing_left) {
                check_aiming_angle(aim_baz_up_an, new_aiming_angle, old_aiming_angle);
            } else {
                check_aiming_angle(aim_baz_down_an, new_aiming_angle, old_aiming_angle);
            }
        } else if (angle < 0) {
            if (!facing_left) {
                check_aiming_angle(aim_baz_down_an, new_aiming_angle, old_aiming_angle);
            } else {
                check_aiming_angle(aim_baz_up_an, new_aiming_angle, old_aiming_angle);
            }
        } else {
            check_aiming_angle(aim_baz_an, new_aiming_angle, old_aiming_angle);
        }
        break;
    default:
        break;
    }
}

void WormAnimations::check_aiming_angle(AnimationScroll& an, int new_aiming_angle, int old_aiming_angle) {
    if(new_aiming_angle > old_aiming_angle) {
        an.update_once_down();
    } else if (new_aiming_angle < old_aiming_angle) {
        an.update_once_up();
    }
}

void WormAnimations::update_from_iter(int state, int angle, bool facing_left) {
    if((!is_action_state(state)) and (!lingering_animations.empty())) {
        if(!(lingering_animations.front().get().update_once())) {
            lingering_animations.front().get().reset();
            lingering_animations.pop_front();
        }
        return;
    }

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

void WormAnimations::push_back_with_angle(Animation& middle_an, Animation& down_an, Animation& up_an, int angle, const bool facing_left) {
    if(angle > 0) {
        if (!facing_left) {
            lingering_animations.push_back(up_an);
        } else {
            lingering_animations.push_back(down_an);
        }
    } else if (angle < 0) {
        if (!facing_left) {
            lingering_animations.push_back(down_an);
        } else {
            lingering_animations.push_back(up_an);
        }
    } else {
        lingering_animations.push_back(middle_an);
    }
}

void WormAnimations::push_drop_weapon_an(TOOLS weapon, int angle, const bool facing_left) {
    switch (weapon) {
        case BAZOOKA:
            push_back_with_angle(drop_baz_an, drop_baz_down_an, drop_baz_up_an, angle, facing_left);
            break;
        case MORTAR:
            // lingering_animations.push_back();
            break;
        case GREEN_GRENADE:
            // lingering_animations.push_back();
            break;
        case HOLY_GRENADE:
            // lingering_animations.push_back();
            break;
        case DYNAMITE:
            // lingering_animations.push_back();
            break;
        case BASEBALL_BAT:
            // lingering_animations.push_back();
            break;
        case RED_GRENADE:
            // lingering_animations.push_back();
            break;
        case BANANA:
            // lingering_animations.push_back();
            break;
        case AIRSTRIKE:
            // lingering_animations.push_back();
            break;
        case TELEPORTATION:
            // lingering_animations.push_back();
            break;
        case NO_TOOL:
            break;
    }
}

void WormAnimations::push_pick_up_weapon_an(TOOLS weapon, int angle, const bool facing_left) {
    switch (weapon) {
        case BAZOOKA:
            push_back_with_angle(get_baz_an, get_baz_down_an, get_baz_up_an, angle, facing_left);
            break;
        case MORTAR:
            // lingering_animations.push_back();
            break;
        case GREEN_GRENADE:
            // lingering_animations.push_back();
            break;
        case HOLY_GRENADE:
            // lingering_animations.push_back();
            break;
        case DYNAMITE:
            // lingering_animations.push_back();
            break;
        case BASEBALL_BAT:
            // lingering_animations.push_back();
            break;
        case RED_GRENADE:
            // lingering_animations.push_back();
            break;
        case BANANA:
            // lingering_animations.push_back();
            break;
        case AIRSTRIKE:
            // lingering_animations.push_back();
            break;
        case TELEPORTATION:
            // lingering_animations.push_back();
            break;
        case NO_TOOL:
            break;
    }
}

void WormAnimations::update_changing_weapons(TOOLS actual_weapon, TOOLS new_weapon, int angle, const bool facing_left) {
    push_drop_weapon_an(actual_weapon, angle, facing_left);
    push_pick_up_weapon_an(new_weapon, angle, facing_left);
}

bool WormAnimations::is_action_state(int state) {
    bool is_moving_state = (state == MOVING);
    bool is_climbing_state = (state == CLIMBING);
    bool is_jumping_state = (state == JUMPING);
    bool is_sliding_state = (state == SLIDING);
    bool is_backflipping_state = (state == BACKFLIPPING);
    bool is_falling_state = (state == FALLING);
    return (is_moving_state or is_climbing_state or is_jumping_state or is_sliding_state or is_backflipping_state or is_falling_state);
}