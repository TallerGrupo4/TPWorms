#include "worm.h"

Worm::Worm(WormSnapshot worm_snpsht, int worm_width, int worm_height, std::shared_ptr<EffectsAnimations>& effects_an, std::shared_ptr<EffectsSounds>& effects_sound, ArmyColorDependentMisc widgets, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : 
    effects_an(effects_an),
    effects_sound(effects_sound),
    facing_left(worm_snpsht.direction == LEFT ? true : false),
    moving(false),
    angle(worm_snpsht.angle),
    id(worm_snpsht.id),
    health_points(worm_snpsht.health),
    max_health(worm_snpsht.max_health),
    state(worm_snpsht.state),
    weapon(static_cast<TOOLS>(worm_snpsht.weapon)),
    weapon_ammo(worm_snpsht.current_ammo),
    aiming_angle(worm_snpsht.aiming_angle),
    x(worm_snpsht.pos_x),
    y((-1)*worm_snpsht.pos_y),
    width(worm_width),
    height(worm_height),
    army_id(worm_snpsht.team_id),
    worm_an(renderer, surfaces, state, angle, weapon, weapon_ammo, facing_left, aiming_angle),
    worm_texts(renderer, army_id, widgets, id, health_points, max_health) {}

Worm::~Worm() {}

int Worm::get_worm_state() {
    return this->state;
}

int Worm::get_worm_x() {
    return this->x;
}

int Worm::get_worm_y() {
    return this->y;
}

TOOLS Worm::get_weapon() {
    return this->weapon;
}

int Worm::get_weapon_ammo() {
    return this->weapon_ammo;
}

bool Worm::has_weapon() {
    return this->weapon != TOOLS::NO_TOOL;
}

bool Worm::has_dynamite() {
    return this->weapon == TOOLS::DYNAMITE;
}

bool Worm::has_weapon_to_aim() {
    bool dont_have_weapon = (this->weapon == TOOLS::NO_TOOL);
    bool is_weapon_dynamite = (this->weapon == TOOLS::DYNAMITE);
    bool is_weapon_airstrike = (this->weapon == TOOLS::AIRSTRIKE);
    bool is_weapon_teleport = (this->weapon == TOOLS::TELEPORTATION);
    return (!(dont_have_weapon or is_weapon_dynamite or is_weapon_airstrike or is_weapon_teleport));
}

bool Worm::has_charging_weapon() {
    bool is_weapon_baseball_bat = (this->weapon == TOOLS::BASEBALL_BAT);
    return (has_weapon_to_aim() and (!is_weapon_baseball_bat));
}

bool Worm::has_timer_weapon() {
    bool dont_have_weapon = (this->weapon == TOOLS::NO_TOOL);
    bool is_weapon_bazooka = (this->weapon == TOOLS::BAZOOKA);
    bool is_weapon_mortar = (this->weapon == TOOLS::MORTAR);
    bool is_weapon_baseball_bat = (this->weapon == TOOLS::BASEBALL_BAT);
    bool is_weapon_airstrike = (this->weapon == TOOLS::AIRSTRIKE);
    bool is_weapon_teleport = (this->weapon == TOOLS::TELEPORTATION);
    return (!(dont_have_weapon or is_weapon_bazooka or is_weapon_mortar or is_weapon_baseball_bat or is_weapon_airstrike or is_weapon_teleport));
}

bool Worm::has_guided_weapon() {
    bool is_weapon_airstrike = (this->weapon == TOOLS::AIRSTRIKE);
    bool is_weapon_teleport = (this->weapon == TOOLS::TELEPORTATION);
    return (is_weapon_airstrike or is_weapon_teleport);
}

bool Worm::worm_facing_left() {
    return this->facing_left;
}

char Worm::get_army_id() {
    return this->army_id;
}

void Worm::update_from_snapshot(SDL2pp::Renderer& renderer, WormSnapshot& worm_snpsht) {
    int old_state = state;
    TOOLS old_weapon = weapon;
    
    weapon_ammo = worm_snpsht.current_ammo;
    angle = worm_snpsht.angle;
    facing_left = (worm_snpsht.direction == LEFT);
    health_points = worm_snpsht.health;
    worm_texts.update_health(health_points, max_health);
    state = worm_snpsht.state;
    aiming_angle = worm_snpsht.aiming_angle;
    worm_texts.update_crosshair(aiming_angle);
    TOOLS new_weapon = static_cast<TOOLS>(worm_snpsht.weapon);
    if (old_weapon != new_weapon) {
        worm_an.update_changing_weapons(new_weapon, weapon_ammo, angle, facing_left);
        weapon = new_weapon;
    }
    y = (-1)*worm_snpsht.pos_y;
    x = worm_snpsht.pos_x;
    switch (state) {
    case JUMPING:
    case BACKFLIPPING:
        if(old_state == STILL) effects_sound->play_worm_jump_sound();
        break;
    case DAMAGED:
        effects_an->set_worm_hit_an(renderer, x, y);
        effects_sound->play_worm_impact_sound();
        break;
    case SHOOTED:
        handleShootedState(renderer, old_weapon);
        break;
    case DEAD:
        effects_sound->play_worm_death_sound();
        break;
    default:
        break;
    }
    worm_an.update_from_snapshot(state, angle, facing_left, weapon, weapon_ammo, aiming_angle);
}

void Worm::handleShootedState(SDL2pp::Renderer& renderer, TOOLS old_weapon) {
    switch (old_weapon) {
    case TOOLS::BASEBALL_BAT: {
        int baseball_hit_pos_x = x + worm_texts.get_crosshair_x();
        int baseball_hit_pos_y = y + worm_texts.get_crosshair_y();
        effects_an->set_baseball_bat_hit(renderer, baseball_hit_pos_x, baseball_hit_pos_y);
        effects_sound->play_baseball_bat_sound();
        }
        break;
    case TOOLS::TELEPORTATION:
        effects_sound->play_teleport_sound();
        break;
    case TOOLS::AIRSTRIKE:
        effects_sound->play_airstrike_active_sound();
        break;
    default:
        break;
    }
}

void Worm::update_from_iter(int iter) {
    for (int i = 0; i < iter; i++) {
        worm_an.update_from_iter(state, angle, facing_left);
        worm_texts.update_crosshair_from_iter();
    }
}

void Worm::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    int top_left_x = (x-width/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_left_y = (y-height/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;
    
    worm_an.render(state, angle, weapon, weapon_ammo, renderer, SDL2pp::Rect(top_left_x, top_left_y, width*RESOLUTION_MULTIPLIER,
                        height*RESOLUTION_MULTIPLIER),
                        facing_left,
                        WORM_WALK_LEFT_OFFSET,
                        WORM_WALK_RIGHT_OFFSET,
                        WORM_WALK_ABOVE_OFFSET,
                        WORM_WALK_BELLOW_OFFSET);
}

void Worm::render_texts_and_widgets(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    int center_x = x*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_y = (y-height/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;
    
    if(state != DEAD) {
        worm_texts.render(renderer, state, facing_left, center_x, top_y + height*RESOLUTION_MULTIPLIER/2, top_y, top_y + height*RESOLUTION_MULTIPLIER);
    }
}