#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "projectile_animations.h"
#include "surfaces.h"
#include "Animation.h"
#include "background.h"

class Projectile {
public:
    Projectile(ProjectileSnapshot proj_snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void update_from_snapshot(ProjectileSnapshot& proj_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    ProjectileStates get_proj_state();
    int get_proj_x();
    int get_proj_y();
    bool proj_facing_left();
private:
    ProjectileAnimations proj_an;
    bool facing_left;
    int angle;
    char id;
    ProjectileStates state;
    ProjectileTypes type;
    int x;
    int y;
    int explosion_type;
    int width;
    int height;
};

#endif  // PROJECTILE_H