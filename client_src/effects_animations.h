#ifndef EFFECTS_ANIMATIONS_H
#define EFFECTS_ANIMATIONS_H

#include <memory>
#include <list>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "client_constants.h"
#include "surfaces.h"
#include "Animation.h"

class PosAndAnimation {
private:
    int x;
    int y;
    int explosion_size;
    Animation an;
public:
    PosAndAnimation(int x, int y, SDL2pp::Renderer& renderer, SDL2pp::Surface& surface, uint seconds_for_an, bool an_is_looped, int explosion_size=0) : x(x), y(y), explosion_size(explosion_size), an(renderer, surface, seconds_for_an, an_is_looped) {}
    int get_x() { return x; }
    int get_y() { return y; }
    int get_explosion_size() {return explosion_size;}
    Animation& get_an() { return an; }
};

class EffectsAnimations {
public:
    EffectsAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(SDL2pp::Renderer& renderer, int camara_offset_x, int camera_offset_y);
    void set_worm_hit_an(SDL2pp::Renderer& renderer, int x, int y);
    void set_baseball_bat_hit(SDL2pp::Renderer& renderer, int x, int y);
    void set_big_explosion_an(SDL2pp::Renderer& renderer, int x, int y, int explosion_size = 0);
    void set_small_explosion_an(SDL2pp::Renderer& renderer, int x, int y, int explosion_size = 0);
    void set_missile_exhaust_an(SDL2pp::Renderer& renderer, int x, int y);
    void update_from_iter();
private:
    void renderAnimation(Animation& animation, SDL2pp::Renderer& renderer, int size, int x, int y, SDL_RendererFlip flip, int camera_offset_x, int camera_offset_y);

    std::list<std::unique_ptr<PosAndAnimation>> lingering_animations;
    /*NEED OF ITER*/
    SDL2pp::Surface& small_explosion_circle_surface;
    SDL2pp::Surface& big_explosion_circle_surface;
    SDL2pp::Surface& small_explosion_rings_surface;
    SDL2pp::Surface& big_explosion_rings_surface;
    SDL2pp::Surface& missile_exhaust_surface;
    SDL2pp::Surface& baseball_bat_hit_surface;
    SDL2pp::Surface& worm_hit_surface;
};

#endif  // EFFECTS_ANIMATIONS_H