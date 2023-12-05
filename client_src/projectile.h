#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "../common_src/snapshot.h"

#include "Animation.h"
#include "client_constants.h"
#include "effects_animations.h"
#include "effects_sounds.h"
#include "projectile_animations.h"
#include "surfaces.h"

class Projectile {
public:
    Projectile(const ProjectileSnapshot& proj_snpsht,
               std::shared_ptr<EffectsAnimations>& effects_an,
               std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces,
               SDL2pp::Renderer& renderer);
    void update_from_snapshot(SDL2pp::Renderer& renderer, ProjectileSnapshot& proj_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    ProjectileStates get_proj_state();
    int get_proj_x();
    int get_proj_y();

private:
    ProjectileAnimations proj_an;
    std::shared_ptr<EffectsAnimations> effects_an;
    std::shared_ptr<EffectsSounds> effects_sound;
    bool facing_left;
    int angle;
    char id;
    ProjectileStates state;
    ProjectileTypes type;
    int x;
    int y;
    int explosion_size;
    int width;
    int height;
    int exhaust_timer;
};

#endif  // PROJECTILE_H
