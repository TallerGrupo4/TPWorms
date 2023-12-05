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

// Class that represents a projectile in the match
class Projectile {
public:
    /**
     * @brief Construct a new Projectile object
     * @param proj_snpsht Snapshot of the projectile received from the server
     * @param effects_an Effects animations
     * @param effects_sound Effects sounds
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     */
    Projectile(const ProjectileSnapshot& proj_snpsht,
               std::shared_ptr<EffectsAnimations>& effects_an,
               std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces,
               SDL2pp::Renderer& renderer);
    /**
     * @brief Updates the projectile from a snapshot received from the server
     * @param renderer Renderer of the match
     * @param proj_snpsht Snapshot of the projectile received from the server
     */
    void update_from_snapshot(SDL2pp::Renderer& renderer, ProjectileSnapshot& proj_snpsht);
    /**
     * @brief Updates the projectile from the ticks of the match
     * @param iter Iterations needed to update all the ticks
     */
    void update_from_iter(int iter);
    /**
     * @brief Renders the projectile
     * @param renderer Renderer of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    /**
     * @brief Returns the state of the projectile
     * @return State of the projectile
     */
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
