#include "match.h"
#include <iostream>
#include "constantes_cliente.h"
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, SDL2pp::Mixer& mixer) : 
            bkgrnd(std::make_shared<Background>(snpsht.platforms, snpsht.map_dimensions.width, snpsht.map_dimensions.height, snpsht.map_dimensions.water_level, surfaces, renderer)),
            effects_an(std::make_shared<EffectsAnimations>(renderer, surfaces)),
            effects_sound(std::make_shared<EffectsSounds>(mixer)),
            my_army_id(snpsht.my_army.begin()->first),
            worm_turn_id(snpsht.turn_time_and_worm_turn.worm_turn),
            turn_time(snpsht.turn_time_and_worm_turn.turn_time/FPS),
            camera(renderer, surfaces, turn_time, my_army_id, snpsht.map_dimensions.width, snpsht.map_dimensions.height),
            charge_for_weapon(0),
            timer_for_weapon(0),
            already_shot_charged_weapon(false) {

    camera.update_turn_time_text(turn_time);

    std::map<int, std::pair<std::reference_wrapper<SDL2pp::Surface>, SDL_Color>> team_info = {
        {0, {surfaces.crosshair_blue, BLUE}},
        {1, {surfaces.crosshair_red, RED}},
        {2, {surfaces.crosshair_yellow, YELLOW}},
        {3, {surfaces.crosshair_green, GREEN}},
        {4, {surfaces.crosshair_purple, ORANGE}}
    };

    for (WormSnapshot worm_snpsht : snpsht.worms){
        std::pair<std::reference_wrapper<SDL2pp::Surface>, SDL_Color> widgets_info = (worm_snpsht.team_id > 3) ? team_info.at(4) : team_info.at(worm_snpsht.team_id);
        ArmyColorDependentMisc widgets(widgets_info.first.get(), widgets_info.second);
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, effects_sound, widgets, surfaces, renderer, bkgrnd);
        this->worms_map[worm_snpsht.id] = worm;
    }

    for (auto& provision_box_snpsht : snpsht.provision_boxes) {
        std::shared_ptr<ProvisionBox> provision_box = std::make_shared<ProvisionBox>(provision_box_snpsht, effects_an, effects_sound, surfaces, renderer);
        this->provision_boxes_map[provision_box_snpsht.id] = provision_box;
    }

    update_camera(1,1,true);
}

void Match::update_from_snapshot(Snapshot& snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    if(snpsht.get_end_game() and !snpsht.worms.empty()) {
        char winner_team_id = snpsht.worms.front().team_id;
        camera.set_end_game(winner_team_id);
        effects_sound->play_match_finnished_sound();
    }

    uint new_turn_time = (snpsht.turn_time_and_worm_turn.turn_time / FPS);
    if (turn_time != new_turn_time) {
        turn_time = new_turn_time;
        camera.update_turn_time_text(turn_time);    
    }

    for (auto it = projectiles_map.begin(); it != projectiles_map.end();) {
        if (it->second->get_proj_state() == EXPLODED) {
            Target new_target = {
                    PlayerType,
                    -1,
                    -1,
                    camera.get_offset_x(),
                    camera.get_offset_y()
                };
            camera.update(new_target);
            it = projectiles_map.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = provision_boxes_map.begin(); it != provision_boxes_map.end();) {
        if (it->second->get_box_state() == PICKED) {
            it = provision_boxes_map.erase(it);
        } else {
            ++it;
        }
    }

    for (auto& projectile_snpsht : snpsht.projectiles) {
        auto& projectile = projectiles_map[projectile_snpsht.id];
        if(!projectile) {
            projectile = std::make_shared<Projectile>(projectile_snpsht, effects_an, effects_sound, surfaces, renderer);
        } else {
            projectile->update_from_snapshot(renderer, projectile_snpsht);
        }
    }

    for (auto& provision_box_snpsht : snpsht.provision_boxes) {
        auto& provision_box = provision_boxes_map[provision_box_snpsht.id];
        if(!provision_box) {
            provision_box = std::make_shared<ProvisionBox>(provision_box_snpsht, effects_an, effects_sound, surfaces, renderer);
        } else {
            provision_box->update_from_snapshot(renderer, provision_box_snpsht);
        }
    }

    for (auto& worm_snpsht : snpsht.worms) { 
        worms_map.at(worm_snpsht.id)->update_from_snapshot(renderer, worm_snpsht);
    }
    auto worm_turn = snpsht.turn_time_and_worm_turn.worm_turn;
    if (worm_turn_id != worm_turn) {
        worm_turn_id = worm_turn;
        camera.take_out_marker();
        already_shot_charged_weapon = false;
        update_camera(1,1,true);
    } else {
        update_camera();
    }
    auto worm_turn_worm = worms_map.at(worm_turn_id);
    char worm_turn_army_id = worm_turn_worm->get_army_id();
    camera.update_turn_weapon(worm_turn_worm->get_weapon());
    if(worm_turn_worm->has_weapon()) {
        camera.update_turn_weapon_ammo(worm_turn_worm->get_weapon_ammo());
    }
    camera.set_army_turn(worm_turn_army_id);
    camera.update_armies_health(snpsht.armies_health);
    camera.update_wind_velocity(snpsht.get_wind_force());
}

bool Match::get_next_target(Target& new_target) {
    for (auto& worm_pair : worms_map) {
        auto& worm = worm_pair.second;
        if((worm->get_worm_state() != STILL) and (worm->get_worm_state() != DEAD)) {
            new_target = {
                WormType,
                worm_pair.first,
                -1,
                worm->get_worm_x()*RESOLUTION_MULTIPLIER,
                worm->get_worm_y()*RESOLUTION_MULTIPLIER,
            };
            return true;
        }
    }
    for (auto& projectile_pair : projectiles_map) {
        auto& projectile = projectile_pair.second;
        if(projectile->get_proj_state() != EXPLODED) {
            new_target = {
                ProjectileType,
                -1,
                projectile_pair.first,
                projectile->get_proj_x()*RESOLUTION_MULTIPLIER,
                projectile->get_proj_y()*RESOLUTION_MULTIPLIER,
            };
            return true;
        }
    }
    return false;
}

void Match::update_camera_for_less_priority_targets(int camera_offset_x, int camera_offset_y, bool center_camera) {
    Target new_target;
    if (center_camera) {
        new_target = {
            WormType,
            get_turn_worm_id(),
            -1,
            get_turn_worm_x()*RESOLUTION_MULTIPLIER,
            get_turn_worm_y()*RESOLUTION_MULTIPLIER
        };
        camera.update(new_target);
    } else if(get_next_target(new_target)) {
            camera.update(new_target);
    } else if ((camera_offset_x != 0) and (camera_offset_y != 0)) {
            new_target = {
                PlayerType,
                -1,
                -1,
                camera_offset_x + get_turn_worm_x()*RESOLUTION_MULTIPLIER,
                camera_offset_y + get_turn_worm_y()*RESOLUTION_MULTIPLIER
            };
            camera.update(new_target);
    }
}

void Match::update_camera(int camera_offset_x, int camera_offset_y,
                         bool center_camera, bool player_activated,
                         bool need_to_be_player_activated) { 
    if(!camera.is_player_activated() and need_to_be_player_activated) {
        return;
    }
    if (player_activated) {
        camera.toogle_player_activated();
    }
    
    TargetType target_type = this->camera.has_target();
    Target new_target;
    switch (target_type) {
    case WormType: {
        auto target_worm = worms_map.at(camera.get_target_worm_id());
        if((target_worm->get_worm_state() != STILL) and (target_worm->get_worm_state() != DEAD)) {
            new_target = {
                WormType,
                camera.get_target_worm_id(),
                -1,
                target_worm->get_worm_x()*RESOLUTION_MULTIPLIER,
                target_worm->get_worm_y()*RESOLUTION_MULTIPLIER,
            };
            camera.update(new_target);
            break;
        }
    }
    case NoneType:
    case PlayerType:
        update_camera_for_less_priority_targets(camera_offset_x, camera_offset_y, center_camera);
        break;
    case ProjectileType:
        auto target_proj = projectiles_map.at(camera.get_target_proj_id());
        
        if(target_proj->get_proj_state() != EXPLODED) {
            new_target = {
                ProjectileType,
                -1,
                camera.get_target_proj_id(),
                target_proj->get_proj_x()*RESOLUTION_MULTIPLIER,
                target_proj->get_proj_y()*RESOLUTION_MULTIPLIER,
            };
            camera.update(new_target);
            break;
        }
        update_camera_for_less_priority_targets(camera_offset_x, camera_offset_y, center_camera);
        break;
    }
}

void Match::update_from_iter(int iter) {
    bkgrnd->update_water();
    for (auto& worm : worms_map) {
        worm.second->update_from_iter(iter);
    }
    for (auto& projectile : projectiles_map) {
        projectile.second->update_from_iter(iter);
    }
    for (auto& provision_box : provision_boxes_map) {
        provision_box.second->update_from_iter(iter);
    }
    camera.update_hud();
    effects_an->update_from_iter();
    update_camera();
}

void Match::render(SDL2pp::Renderer& renderer) {
    int offset_x = this->camera.get_offset_x();
    int offset_y = this->camera.get_offset_y();
    bkgrnd->render(renderer, offset_x, offset_y);
    for (auto& worm_pair : worms_map) {
        worm_pair.second->render(renderer, offset_x, offset_y);
    }
    for (auto& worm_pair_for_hud : worms_map) {
        worm_pair_for_hud.second->render_texts_and_widgets(renderer, offset_x, offset_y);
    }
    for (auto& box_pair : provision_boxes_map) {
        box_pair.second->render(renderer, offset_x, offset_y);
    }
    for (auto& proj_pair : projectiles_map) {
        proj_pair.second->render(renderer, offset_x, offset_y);
    }
    bkgrnd->render_water(renderer, offset_x, offset_y);
    this->effects_an->render(renderer, offset_x, offset_y);
    this->camera.render(renderer);
}

bool Match::handle_left_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_aiming_weapon()) {
            std::cout << "ENTRE PARA MANDAR QUE MIRE PARA LA IZQ con el aim\n";
            action = std::make_shared<ActionAim>(LEFT, CENTER, worm_turn_id);
            return true;
        }
        if (!turn_worm_has_weapon()) {
            action = std::make_shared<ActionMovLeft>(worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_right_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_aiming_weapon()) {
            std::cout << "ENTRE PARA MANDAR QUE MIRE PARA LA DER con el aim\n";
            action = std::make_shared<ActionAim>(RIGHT, CENTER, worm_turn_id);
            return true;
        } 
        if (!turn_worm_has_weapon()) {
            action = std::make_shared<ActionMovRight>(worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_up_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and is_turn_worm_aiming_weapon()) {
        std::cout << "ENTRE PARA MANDAR QUE MIRE PARA ARRiba con el aim\n";
        action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, UP, worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_down_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and is_turn_worm_aiming_weapon()) {
        std::cout << "ENTRE PARA MANDAR QUE MIRE PARA ABAJO con el aim\n";
        action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, DOWN, worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_space_button_pressed(std::shared_ptr<Action>& action, bool first_time_pressed) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_charging_weapon() and is_turn_worm_aiming_weapon() and (!already_shot_charged_weapon)) {
            if (first_time_pressed) effects_sound->play_powerup_sound();
            charge_for_weapon += 2;
            if(charge_for_weapon == 100) {
                std::cout << "Sending ActionShoot in space pressed with charge: " << charge_for_weapon << std::endl;
                action = std::make_shared<ActionShooting>(100, worm_turn_id);
                charge_for_weapon = 0;
                camera.clear_charging_value();
                already_shot_charged_weapon = true;
                return true;
            }
            camera.set_charging_value(charge_for_weapon);
        }
    }
    return false;
}

bool Match::handle_space_button_release(std::shared_ptr<Action>& action, SDL2pp::Renderer& renderer) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_charging_weapon() and is_turn_worm_aiming_weapon()) {
            action = std::make_shared<ActionShooting>(charge_for_weapon, worm_turn_id, timer_for_weapon);
            charge_for_weapon = 0;
            camera.clear_charging_value();
            if(turn_worm_has_timer_weapon()) {
                camera.clear_timer_value();
                timer_for_weapon = 0;
            }
            return true;
        } else if (turn_worm_has_guided_weapon() and camera.is_marker_set()) {
            int target_x = (camera.get_marker_x() - (int)(renderer.GetLogicalWidth()/2))/RESOLUTION_MULTIPLIER;
            int target_y = (camera.get_marker_y() - (int)(renderer.GetLogicalHeight()/2))/RESOLUTION_MULTIPLIER;
            action = std::make_shared<ActionShooting>(0, worm_turn_id, 0, target_x, target_y);
            camera.take_out_marker();
            return true;
        } else if(turn_worm_has_dynamite()) {
            action = std::make_shared<ActionShooting>(0, worm_turn_id, timer_for_weapon);
            camera.clear_timer_value();
            timer_for_weapon = 0;
            return true;
        } else if(is_turn_worm_aiming_weapon()) {
            action = std::make_shared<ActionShooting>(0, worm_turn_id);
            return true;
        
        }
    }
    return false;
}

void Match::handle_1_button() {
    if(is_turn_worm_in_my_army() and turn_worm_has_timer_weapon()) {
        camera.set_timer(1);
        timer_for_weapon = 1;
    }
}

void Match::handle_2_button() {
    if(is_turn_worm_in_my_army() and turn_worm_has_timer_weapon()) {
        camera.set_timer(2);
        timer_for_weapon = 2;
    }
}

void Match::handle_3_button() {
    if(is_turn_worm_in_my_army() and turn_worm_has_timer_weapon()) {
        camera.set_timer(3);
        timer_for_weapon = 3;
    }
}

void Match::handle_4_button() {
    if(is_turn_worm_in_my_army() and turn_worm_has_timer_weapon()) {
        camera.set_timer(4);
        timer_for_weapon = 4;
    }
}

void Match::handle_5_button() {
    if(is_turn_worm_in_my_army() and turn_worm_has_timer_weapon()) {
        camera.set_timer(5);
        timer_for_weapon = 5;
    }
}

bool Match::handle_cheat_1(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        action = std::make_shared<ActionCheatExtraLife>(worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_cheat_2(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        action = std::make_shared<ActionCheatExtraAmmo>(worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_cheat_3(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        action = std::make_shared<ActionExtraTurnTime>(worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_cheat_4(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        action = std::make_shared<ActionExtraShooting>(worm_turn_id);
        return true;
    }
    return false;
}


void Match::handle_mouse_left_click(int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army() and turn_worm_has_guided_weapon()) {
        camera.set_marker_position(mouse_x, mouse_y);
    }
}

bool Match::handle_mouse_right_click(std::shared_ptr<Action>& action, int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_still() and turn_worm_has_weapon_to_aim()) {
            if(turn_worm_has_timer_weapon()) {
                camera.set_timer(5);
                timer_for_weapon = 5;
            }
            action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, CENTER, worm_turn_id);
            return true;
        } else if (is_turn_worm_still() and turn_worm_has_guided_weapon()) {
            camera.follow_mouse_with_marker(mouse_x, mouse_y);
        } else if (is_turn_worm_still() and turn_worm_has_timer_weapon()) {
            camera.set_timer(5);
            timer_for_weapon = 5;
        }
    }
    return false;
}

bool Match::handle_mouse_scroll_up(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and ((is_turn_worm_still() and !turn_worm_has_guided_weapon()) or (is_turn_worm_still() and turn_worm_has_guided_weapon() and !camera.is_marker_active()))) {
        action = std::make_shared<ActionChangeWeapon>(SCROLL_UP, worm_turn_id);
        return true;
    }
    return false;
}

bool Match::handle_mouse_scroll_down(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and ((is_turn_worm_still() and !turn_worm_has_guided_weapon()) or (is_turn_worm_still() and turn_worm_has_guided_weapon() and !camera.is_marker_active()))) {
        action = std::make_shared<ActionChangeWeapon>(SCROLL_DOWN, worm_turn_id);
        return true;
    }
    return false;
}

void Match::handle_mouse_motion(int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army() and is_turn_worm_still() and turn_worm_has_guided_weapon() and camera.is_marker_active() and (!camera.is_marker_set())) {
        camera.update_marker(mouse_x, mouse_y);
    }
}

bool Match::handle_enter_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and (!is_turn_worm_aiming_weapon()) and (!turn_worm_has_weapon())) {
        action = std::make_shared<ActionJump>(worm_turn_id);
        return true;
    }
    return false;
}
bool Match::handle_backspace_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army() and (!is_turn_worm_aiming_weapon()) and (!turn_worm_has_weapon())) {
        action = std::make_shared<ActionBackflip>(worm_turn_id);
        return true;
    }
    return false;
}

int Match::get_turn_worm_x() {
    return worms_map.at(worm_turn_id)->get_worm_x();
}

int Match::get_turn_worm_y() {
    return worms_map.at(worm_turn_id)->get_worm_y();
}
 
bool Match::turn_worm_facing_left() {
    return worms_map.at(worm_turn_id)->worm_facing_left();
}

char Match::get_turn_worm_id() {
    return worm_turn_id;
}

bool Match::is_turn_worm_in_my_army() {
    return worms_map.at(worm_turn_id)->get_army_id() == my_army_id;
}

bool Match::is_turn_worm_still() {
    return worms_map.at(worm_turn_id)->get_worm_state() == STILL;
}

bool Match::turn_worm_has_dynamite() {
    return worms_map.at(worm_turn_id)->has_dynamite();
}

bool Match::turn_worm_has_weapon() {
    return worms_map.at(worm_turn_id)->has_weapon();
}

bool Match::turn_worm_has_weapon_to_aim() {
    return worms_map.at(worm_turn_id)->has_weapon_to_aim();
}

bool Match::turn_worm_has_charging_weapon() {
    return worms_map.at(worm_turn_id)->has_charging_weapon();
}

bool Match::turn_worm_has_timer_weapon() {
    return worms_map.at(worm_turn_id)->has_timer_weapon();
}

bool Match::turn_worm_has_guided_weapon() {
    return worms_map.at(worm_turn_id)->has_guided_weapon();
}

bool Match::is_turn_worm_aiming_weapon() {
    return worms_map.at(worm_turn_id)->get_worm_state() == AIMING;
}