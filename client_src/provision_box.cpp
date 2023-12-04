#include "provision_box.h"

ProvisionBox::ProvisionBox(ProvisionBoxSnapshot box_snpsht, std::shared_ptr<EffectsAnimations>& effects_an, std::shared_ptr<EffectsSounds>& effects_sound, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : 
    box_an(renderer, surfaces),
    effects_an(effects_an),
    effects_sound(effects_sound),
    id(box_snpsht.id),
    state(box_snpsht.state),
    type(box_snpsht.type),
    x(box_snpsht.pos_x),
    y((-1)*box_snpsht.pos_y),
    width(box_snpsht.width),
    height(box_snpsht.height) {}

void ProvisionBox::update_from_snapshot(SDL2pp::Renderer& renderer, ProvisionBoxSnapshot& box_snpsht) {
    state = box_snpsht.state;
    x = box_snpsht.pos_x;
    y = (-1)*box_snpsht.pos_y;

    switch (state) {
    case BoxState::PICKED:
        switch (type) {
        case BoxType::HEALTH_BOX :
        case BoxType::AMMO_BOX :
            effects_sound->play_pickup_box_sound();
            break;
        case BoxType::TRAP_BOX :
            effects_an->set_big_explosion_an(renderer, x, y);
            effects_sound->play_big_explosion_sound();
            break;
        }
        break;
    default:
        break;
    }
}

void ProvisionBox::update_from_iter(int iter) {
    for (int i = 0; i < iter; i++) {
        box_an.update_from_iter(state, type);
    }
}

void ProvisionBox::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    int top_left_x = (x-width/2)*RESOLUTION_MULTIPLIER +(int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_left_y = (y-height/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;

    box_an.render(state, type, renderer, SDL2pp::Rect(top_left_x, top_left_y, width*RESOLUTION_MULTIPLIER,
                        height*RESOLUTION_MULTIPLIER));
}

BoxState ProvisionBox::get_box_state() {
    return this->state;
}
