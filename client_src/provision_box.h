#ifndef PROVISION_BOX_H
#define PROVISION_BOX_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "effects_animations.h"
#include "surfaces.h"
#include "provision_box_animations.h"

class ProvisionBox {
public:
    ProvisionBox(ProvisionBoxSnapshot box_snpsht, std::shared_ptr<EffectsAnimations>& effects_an, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void update_from_snapshot(SDL2pp::Renderer& renderer, ProvisionBoxSnapshot& box_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    BoxState get_box_state();
    int get_box_x();
    int get_box_y();
private:
    ProvisionBoxAnimations box_an;
    std::shared_ptr<EffectsAnimations> effects_an;
    char id;
    BoxState state;
    BoxType type;
    int x;
    int y;
    int width;
    int height;
};

#endif  // PROVISION_BOX_H