#ifndef PROVISION_BOX_ANIMATIONS_H
#define PROVISION_BOX_ANIMATIONS_H

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"

#include "Animation.h"
#include "client_constants.h"
#include "surfaces.h"

// Class that represents the animations of a provision box
class ProvisionBoxAnimations {
public:
    /**
     * @brief Construct a new Provision Box Animations object
     * @param renderer Renderer of the match
     * @param surfaces Surfaces of the match
     */
    ProvisionBoxAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    /**
     * @brief Renders the provision box
     * @param state State of the provision box
     * @param type Type of the provision box
     * @param renderer Renderer of the match
     * @param dst Destination rectangle of the provision box
     * @param left_offset Offset of the left side of the provision box
     * @param right_offset Offset of the right side of the provision box
     * @param above_offset Offset of the top side of the provision box
     * @param bellow_offset Offset of the bottom side of the provision box
     */
    void render(BoxState state, BoxType type, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                int left_offset = 0, int right_offset = 0, int above_offset = 0,
                int bellow_offset = 0);
    /**
     * @brief Updates the provision box from the ticks of the match
     * @param state State of the provision box
     * @param type Type of the provision box
     */
    void update_from_iter(BoxState state, BoxType type);

private:
    BoxType trap_box_disguise;
    /*NEED OF ITER*/
    Animation mcrate_still_an;
    Animation mcrate_picked_an;
    Animation wcrate_still_an;
    Animation wcrate_picked_an;
};

#endif  // PROVISION_BOX_ANIMATIONS_H
