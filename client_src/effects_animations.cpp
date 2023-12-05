#include "effects_animations.h"

EffectsAnimations::EffectsAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces):
        small_explosion_circle_surface(surfaces.small_circle_explosion),
        big_explosion_circle_surface(surfaces.big_circle_explosion),
        small_explosion_rings_surface(surfaces.small_ring_explosion),
        big_explosion_rings_surface(surfaces.big_ring_explosion),
        missile_exhaust_surface(surfaces.missile_exhaust),
        baseball_bat_hit_surface(surfaces.baseball_bat_hit),
        worm_hit_surface(surfaces.worm_hit) {}

void EffectsAnimations::renderAnimation(Animation& animation, SDL2pp::Renderer& renderer, int size,
                                        int x, int y, SDL_RendererFlip flip, int camera_offset_x,
                                        int camera_offset_y) {
    int top_left_x = (x * RESOLUTION_MULTIPLIER) - (size / 2) +
                     (int)(renderer.GetLogicalWidth() / 2) - camera_offset_x;
    int top_left_y = (y * RESOLUTION_MULTIPLIER) - (size / 2) +
                     (int)(renderer.GetLogicalHeight() / 2) - camera_offset_y;
    animation.render(renderer, SDL2pp::Rect(top_left_x, top_left_y, size, size), flip);
}

void EffectsAnimations::render(SDL2pp::Renderer& renderer, int camera_offset_x,
                               int camera_offset_y) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    for (auto& animation_and_pos: lingering_animations) {
        int size_of_explosion = animation_and_pos->get_explosion_size() * 2;
        if (size_of_explosion != 0) {
            renderAnimation(animation_and_pos->get_an(), renderer, size_of_explosion,
                            animation_and_pos->get_x(), animation_and_pos->get_y(), flip,
                            camera_offset_x, camera_offset_y);
        } else {
            renderAnimation(animation_and_pos->get_an(), renderer,
                            animation_and_pos->get_an().get_frame_size(),
                            animation_and_pos->get_x(), animation_and_pos->get_y(), flip,
                            camera_offset_x, camera_offset_y);
        }
    }
}

void EffectsAnimations::set_worm_hit_an(SDL2pp::Renderer& renderer, int x, int y) {
    std::unique_ptr<PosExplosionAndAnimation> worm_hit_an =
            std::make_unique<PosExplosionAndAnimation>(x, y, renderer, worm_hit_surface,
                                                       MILISECS_FOR_WORM_HIT_SPRITES, true);
    lingering_animations.push_back(std::move(worm_hit_an));
}

void EffectsAnimations::set_baseball_bat_hit(SDL2pp::Renderer& renderer, int x, int y) {
    std::unique_ptr<PosExplosionAndAnimation> baseball_bat_hit_an =
            std::make_unique<PosExplosionAndAnimation>(x, y, renderer, baseball_bat_hit_surface,
                                                       MILISECS_FOR_BASEBALL_BAT_HIT_SPRITES, true);
    lingering_animations.push_back(std::move(baseball_bat_hit_an));
}

void EffectsAnimations::set_big_explosion_an(SDL2pp::Renderer& renderer, int x, int y,
                                             int explosion_size) {
    std::unique_ptr<PosExplosionAndAnimation> big_circle_explosion_an =
            std::make_unique<PosExplosionAndAnimation>(x, y, renderer, big_explosion_circle_surface,
                                                       MILISECS_FOR_EXPLOSIONS_SPRITES, true,
                                                       explosion_size);
    lingering_animations.push_back(std::move(big_circle_explosion_an));
    std::unique_ptr<PosExplosionAndAnimation> big_ring_explosion_an =
            std::make_unique<PosExplosionAndAnimation>(x, y, renderer, big_explosion_rings_surface,
                                                       MILISECS_FOR_EXPLOSIONS_SPRITES, true,
                                                       explosion_size);
    lingering_animations.push_back(std::move(big_ring_explosion_an));
}

void EffectsAnimations::set_small_explosion_an(SDL2pp::Renderer& renderer, int x, int y,
                                               int explosion_size) {
    std::unique_ptr<PosExplosionAndAnimation> small_circle_explosion_an =
            std::make_unique<PosExplosionAndAnimation>(
                    x, y, renderer, small_explosion_circle_surface, MILISECS_FOR_EXPLOSIONS_SPRITES,
                    true, explosion_size);
    lingering_animations.push_back(std::move(small_circle_explosion_an));
    std::unique_ptr<PosExplosionAndAnimation> small_ring_explosion_an =
            std::make_unique<PosExplosionAndAnimation>(
                    x, y, renderer, small_explosion_rings_surface, MILISECS_FOR_EXPLOSIONS_SPRITES,
                    true, explosion_size);
    lingering_animations.push_back(std::move(small_ring_explosion_an));
}

void EffectsAnimations::set_missile_exhaust_an(SDL2pp::Renderer& renderer, int x, int y) {
    std::unique_ptr<PosExplosionAndAnimation> missile_exhaust_an =
            std::make_unique<PosExplosionAndAnimation>(x, y, renderer, missile_exhaust_surface,
                                                       MILISECS_FOR_EXHAUST_SPRITES, true);
    lingering_animations.push_back(std::move(missile_exhaust_an));
}

void EffectsAnimations::update_from_iter() {
    auto it = lingering_animations.begin();
    while (it != lingering_animations.end()) {
        if (!it->get()->get_an().update_once()) {
            it = lingering_animations.erase(it);
        } else {
            ++it;
        }
    }
}
