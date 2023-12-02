#ifndef PROVISION_BOX_ANIMATIONS_H
#define PROVISION_BOX_ANIMATIONS_H

#include <cstdlib>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "surfaces.h"
#include "Animation.h"

class ProvisionBoxAnimations {
public:
    ProvisionBoxAnimations(SDL2pp::Renderer& renderer, MatchSurfaces& surfaces);
    void render(BoxState state, BoxType type, SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       int left_offset = 0,
                       int right_offset = 0,
                       int above_offset = 0,
                       int bellow_offset = 0);
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