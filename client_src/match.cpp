#include "match.h"
#include <iostream>
#include "constantes_cliente.h"
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : 
            bkgrnd(std::make_shared<Background>(snpsht.platforms, snpsht.map_dimensions.width, snpsht.map_dimensions.height, surfaces, renderer)),
            effects_an(std::make_shared<EffectsAnimations>(renderer, surfaces)),
            my_army_id(snpsht.my_army.begin()->first),
            worm_turn_id(snpsht.turn_time_and_worm_turn.worm_turn),
            turn_time(snpsht.turn_time_and_worm_turn.turn_time/FPS),
            camera(renderer, surfaces, turn_time, my_army_id, snpsht.map_dimensions.width, snpsht.map_dimensions.height),
            charge_for_weapon(0),
            timer_for_weapon(0) {

    camera.update_turn_time_text(turn_time);


    SDL_Color blue_color = BLUE;
    SDL_Color red_color = RED;
    SDL_Color yellow_color = YELLOW;
    SDL_Color green_color = GREEN;
    SDL_Color orange_color = ORANGE;

    for (WormSnapshot worm_snpsht : snpsht.worms){
        switch (worm_snpsht.team_id) {
            case 0 : {
            ArmyColorDependentMisc blue_widgets(surfaces.crosshair_blue, blue_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, blue_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 1 : {
            ArmyColorDependentMisc red_widgets(surfaces.crosshair_red, red_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, red_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 2 : {
            ArmyColorDependentMisc yellow_widgets(surfaces.crosshair_yellow, yellow_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, yellow_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 3 : {
            ArmyColorDependentMisc green_widgets(surfaces.crosshair_green, green_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, green_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            // worm_army_color = Green;
            }
            break;
            default: {
            ArmyColorDependentMisc orange_widgets(surfaces.crossharir_purple, orange_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, effects_an, orange_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            // worm_army_color = Orange;
            }
            break;
        }
        // std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, color_map, surfaces, renderer, bkgrnd);
        // this->worms_map[worm_snpsht.id] = worm;
        std::cout << "worm_map constructor, worm_id == " << +worm_snpsht.id << std::endl;
    }
    update_camera(1,1,true);
}

void Match::update_from_snapshot(Snapshot& snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    if(snpsht.get_end_game()) {
        if (!snpsht.worms.empty()) {
            char winner_team_id = snpsht.worms.front().team_id;
            camera.set_end_game(winner_team_id);
        }
    }
    if (turn_time != (snpsht.turn_time_and_worm_turn.turn_time/FPS)) {
        turn_time = snpsht.turn_time_and_worm_turn.turn_time/FPS;
        camera.update_turn_time_text(turn_time);    
    }
    for (std::map<char,std::shared_ptr<Projectile>>::iterator it = projectiles_map.begin(); it != projectiles_map.end();) {
        //std::cout << "Inside proj destroyer\n";
        if (it->second->get_proj_state() == EXPLODED) {
            std::cout << "Found proj exploded\n";
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
    for (auto& projectile_snpsht : snpsht.projectiles) {
        //std::cout << "inside proj snapshot\n";
        if (projectiles_map.find(projectile_snpsht.id) == projectiles_map.end() or projectiles_map.count(projectile_snpsht.id) == 0) {
            //std::cout << "Not found proj from snapshot in map\n";
            std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(projectile_snpsht, effects_an, surfaces, renderer);
            this->projectiles_map[projectile_snpsht.id] = projectile;
            //std::cout << "proj_map constructor, proj_id == " << +projectile_snpsht.id << std::endl;
        } else {
            //std::cout << "Found proj from snapshot in map --> update\n";
            projectiles_map.at(projectile_snpsht.id)->update_from_snapshot(renderer, projectile_snpsht);
        }
    }

    for (auto& worm_snpsht : snpsht.worms) { 
        worms_map.at(worm_snpsht.id)->update_from_snapshot(renderer, worm_snpsht);
    }
    if (worm_turn_id != snpsht.turn_time_and_worm_turn.worm_turn) {
        worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
        camera.take_out_marker();
        update_camera(1,1,true);
    } else {
        worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
        update_camera();
    }
    char worm_turn_army_id = worms_map.at(worm_turn_id)->get_army_id();
    camera.update_turn_weapon(worms_map.at(worm_turn_id)->get_weapon());
    camera.set_army_turn(worm_turn_army_id);
}

bool Match::get_next_target(Target& new_target) {
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        if((it->second->get_worm_state() != STILL) and (it->second->get_worm_state() != DEAD)) {
            new_target = {
                WormType,
                it->first,
                -1,
                it->second->get_worm_x()*RESOLUTION_MULTIPLIER,
                it->second->get_worm_y()*RESOLUTION_MULTIPLIER,
            };
            return true;
        }
    }
    for (std::map<char,std::shared_ptr<Projectile>>::iterator it = projectiles_map.begin(); it != projectiles_map.end(); it++) {
        if(it->second->get_proj_state() != EXPLODED) {
            new_target = {
                ProjectileType,
                -1,
                it->first,
                it->second->get_proj_x()*RESOLUTION_MULTIPLIER,
                it->second->get_proj_y()*RESOLUTION_MULTIPLIER,
            };
            return true;
        }
    }
    return false;
}

void Match::update_camera(int camera_offset_x, int camera_offset_y,
                         bool center_camera, bool player_activated,
                         bool need_to_be_player_activated) { 
    if(!camera.is_player_activated() and need_to_be_player_activated) {
        return;
    } else if (player_activated) {
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
        if (center_camera) {
            new_target = {
                WormType,
                get_turn_worm_id(),
                -1,
                get_turn_worm_x()*RESOLUTION_MULTIPLIER,
                get_turn_worm_y()*RESOLUTION_MULTIPLIER
            };
            camera.update(new_target);
        } else {
            if(get_next_target(new_target)) {
                camera.update(new_target);
                break;
            }
            if ((camera_offset_x != 0) and (camera_offset_y != 0)) {
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
        break;
    }
    case NoneType:
    case PlayerType:
        if (center_camera) {
            new_target = {
                WormType,
                get_turn_worm_id(),
                -1,
                get_turn_worm_x()*RESOLUTION_MULTIPLIER,
                get_turn_worm_y()*RESOLUTION_MULTIPLIER
            };
            camera.update(new_target);
        } else {
            if(get_next_target(new_target)) {
                camera.update(new_target);
                break;
            }
            if ((camera_offset_x != 0) and (camera_offset_y != 0)) {
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
        break;
    case ProjectileType:
        try {
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
        } catch (const std::exception& e) {
            std::cout << "Lo encontre putin: " << e.what() << "\n";
        } catch (...) {
            std::cout << "ERROR NOT FOUND\n";
        }
        break;
        if (center_camera) {
            new_target = {
                WormType,
                get_turn_worm_id(),
                -1,
                get_turn_worm_x()*RESOLUTION_MULTIPLIER,
                get_turn_worm_y()*RESOLUTION_MULTIPLIER
            };
            camera.update(new_target);
        } else {
            if(get_next_target(new_target)) {
                camera.update(new_target);
                break;
            }
            if ((camera_offset_x != 0) and (camera_offset_y != 0)) {
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
        break;
    }
}

void Match::update_from_iter(int iter) {
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->update_from_iter(iter);
    }
    for (std::map<char,std::shared_ptr<Projectile>>::iterator it = projectiles_map.begin(); it != projectiles_map.end(); it++) {
        it->second->update_from_iter(iter);
    }
    camera.update_hud();
    effects_an->update_from_iter();
    update_camera();
}

void Match::render(SDL2pp::Renderer& renderer) {
    bkgrnd->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    for (std::map<char,std::shared_ptr<Worm>>::iterator worm_it = worms_map.begin(); worm_it != worms_map.end(); worm_it++) {
        worm_it->second->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    for (std::map<char,std::shared_ptr<Worm>>::iterator worm_hud_it = worms_map.begin(); worm_hud_it != worms_map.end(); worm_hud_it++) {
        worm_hud_it->second->render_texts_and_widgets(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    for (std::map<char,std::shared_ptr<Projectile>>::iterator proj_it = projectiles_map.begin(); proj_it != projectiles_map.end(); proj_it++) {
        proj_it->second->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    this->effects_an->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    this->camera.render(renderer);
}

bool Match::handle_left_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_aiming_weapon()) {
            std::cout << "ENTRE PARA MANDAR QUE MIRE PARA LA IZQ con el aim\n";
            action = std::make_shared<ActionAim>(LEFT, CENTER, worm_turn_id);
            return true;
        } else if (!turn_worm_has_weapon()) {
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
        } else if (!turn_worm_has_weapon()) {
            action = std::make_shared<ActionMovRight>(worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_up_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_aiming_weapon()) {
            std::cout << "ENTRE PARA MANDAR QUE MIRE PARA ARRiba con el aim\n";
            action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, UP, worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_down_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_aiming_weapon()) {
            std::cout << "ENTRE PARA MANDAR QUE MIRE PARA ABAJO con el aim\n";
            action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, DOWN, worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_space_button_pressed(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_charging_weapon() and is_turn_worm_aiming_weapon()) {
            charge_for_weapon += 1;
            if(charge_for_weapon == 100) {
                std::cout << "Sending ActionShoot in space pressed with charge: " << charge_for_weapon << std::endl;
                action = std::make_shared<ActionShooting>(charge_for_weapon, worm_turn_id);
                charge_for_weapon = 0;
                camera.clear_charging_value();
                return true;
            }
            camera.set_charging_value(charge_for_weapon);
            std::cout << "Inside space pressed with charge: " << charge_for_weapon << std::endl;
        }
    }
    return false;
}

bool Match::handle_space_button_release(std::shared_ptr<Action>& action, SDL2pp::Renderer& renderer) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_charging_weapon() and is_turn_worm_aiming_weapon()) {
            std::cout << "Sending ActionShoot in space release with charge: " << charge_for_weapon << std::endl;
            action = std::make_shared<ActionShooting>(charge_for_weapon, worm_turn_id);
            charge_for_weapon = 0;
            camera.clear_charging_value();
            if(turn_worm_has_timer_weapon()) {
                camera.clear_timer_value();
                timer_for_weapon = 0;
            }
            return true;
        } else if (turn_worm_has_guided_weapon() and camera.is_marker_set()) {
            int target_x = camera.get_marker_x() - (int)(renderer.GetLogicalWidth()/2);
            int target_y = camera.get_marker_y() - (int)(renderer.GetLogicalHeight()/2) + 184;
            std::cout << "Target x: " << target_x << " Target y: " << target_y << "\n";
            action = std::make_shared<ActionShooting>(0, worm_turn_id, target_x, target_y);
            camera.take_out_marker();
            return true;
        } else if(turn_worm_has_dynamite()) {
            action = std::make_shared<ActionShooting>(0, worm_turn_id);
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
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_timer_weapon()) {
            camera.set_timer(1);
            timer_for_weapon = 1;
        }
    }
}

void Match::handle_2_button() {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_timer_weapon()) {
            camera.set_timer(2);
            timer_for_weapon = 2;
        }
    }
}

void Match::handle_3_button() {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_timer_weapon()) {
            camera.set_timer(3);
            timer_for_weapon = 3;
        }
    }
}

void Match::handle_4_button() {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_timer_weapon()) {
            camera.set_timer(4);
            timer_for_weapon = 4;
        }
    }
}

void Match::handle_5_button() {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_timer_weapon()) {
            camera.set_timer(5);
            timer_for_weapon = 5;
        }
    }
}


void Match::handle_mouse_left_click(int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_guided_weapon()) {
            camera.set_marker_position(mouse_x, mouse_y);
        }
    //     if(is_turn_worm_aiming_weapon()) {
    //         //action = std::make_shared<ActionShoot>(worm_turn_id);
    //     }
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
    if(is_turn_worm_in_my_army()) {
        if((is_turn_worm_still() and !turn_worm_has_guided_weapon()) or (is_turn_worm_still() and turn_worm_has_guided_weapon() and !camera.is_marker_active())) {
            action = std::make_shared<ActionChangeWeapon>(SCROLL_UP, worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_mouse_scroll_down(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if((is_turn_worm_still() and !turn_worm_has_guided_weapon()) or (is_turn_worm_still() and turn_worm_has_guided_weapon() and !camera.is_marker_active())) {
            action = std::make_shared<ActionChangeWeapon>(SCROLL_DOWN, worm_turn_id);
            return true;
        }
    }
    return false;
}

void Match::handle_mouse_motion(int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army()) {
        if (is_turn_worm_still() and turn_worm_has_guided_weapon() and camera.is_marker_active() and (!camera.is_marker_set())) {
            camera.update_marker(mouse_x, mouse_y);
        }
    }
}

bool Match::handle_enter_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(!is_turn_worm_aiming_weapon() and !turn_worm_has_weapon()) {
            action = std::make_shared<ActionJump>(worm_turn_id);
            return true;
        }
    }
    return false;
}
bool Match::handle_backspace_button(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(!is_turn_worm_aiming_weapon() and !turn_worm_has_weapon()) {
            action = std::make_shared<ActionBackflip>(worm_turn_id);
            return true;
        }
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