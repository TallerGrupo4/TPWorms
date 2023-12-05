#ifndef PROVISION_BOX_H
#define PROVISION_BOX_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "../common_src/snapshot.h"

#include "client_constants.h"
#include "effects_animations.h"
#include "effects_sounds.h"
#include "provision_box_animations.h"
#include "surfaces.h"

// Class that represents a provision box in the match
class ProvisionBox {
public:
    /**
     * @brief Construct a new Provision Box object
     * @param box_snpsht Snapshot of the provision box received from the server
     * @param effects_an Effects animations
     * @param effects_sound Effects sounds
     * @param surfaces Surfaces of the match
     * @param renderer Renderer of the match
     */
    ProvisionBox(const ProvisionBoxSnapshot& box_snpsht,
                 std::shared_ptr<EffectsAnimations>& effects_an,
                 std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces,
                 SDL2pp::Renderer& renderer);
    /**
     * @brief Updates the provision box from a snapshot received from the server
     * @param renderer Renderer of the match
     * @param box_snpsht Snapshot of the provision box received from the server
     */
    void update_from_snapshot(SDL2pp::Renderer& renderer, const ProvisionBoxSnapshot& box_snpsht);
    /**
     * @brief Updates the provision box from the ticks of the match
     * @param iter Iterations needed to update all the ticks
     */
    void update_from_iter(int iter);
    /**
     * @brief Renders the provision box
     * @param renderer Renderer of the match
     * @param camera_offset_x Offset of the camera in the x axis
     * @param camera_offset_y Offset of the camera in the y axis
     */
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    /**
     * @brief Returns the state of the provision box
     * @return State of the provision box
     */
    BoxState get_box_state();

private:
    ProvisionBoxAnimations box_an;
    std::shared_ptr<EffectsAnimations> effects_an;
    std::shared_ptr<EffectsSounds> effects_sound;
    char id;
    BoxState state;
    BoxType type;
    int x;
    int y;
    int width;
    int height;
};

#endif  // PROVISION_BOX_H
