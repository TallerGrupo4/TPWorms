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

class ProvisionBox {
public:
    ProvisionBox(const ProvisionBoxSnapshot& box_snpsht,
                 std::shared_ptr<EffectsAnimations>& effects_an,
                 std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces,
                 SDL2pp::Renderer& renderer);
    void update_from_snapshot(SDL2pp::Renderer& renderer, const ProvisionBoxSnapshot& box_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
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
