#include "match.h"
#include <iostream>
#include "constantes_cliente.h"
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    bkgrnd = std::make_shared<Background>(snpsht.platforms, snpsht.map_dimensions.width, snpsht.map_dimensions.height, surfaces, renderer);
    my_army_id = snpsht.my_army.begin()->first;
    worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
    turn_time = snpsht.turn_time_and_worm_turn.turn_time/FPS;
    charge_for_weapon = 0;
    camera.update_turn_time_text(turn_time);


    SDL_Color blue_color = BLUE;
    SDL_Color red_color = RED;
    SDL_Color yellow_color = YELLOW;
    SDL_Color green_color = GREEN;
    SDL_Color orange_color = ORANGE;

    for (WormSnapshot worm_snpsht : snpsht.worms){
        switch (worm_snpsht.team_id) {
            case 0 : {
            ArmyColorDependentMisc blue_widgets(surfaces.crosshair_blue, surfaces.marker_blue, blue_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, blue_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 1 : {
            ArmyColorDependentMisc red_widgets(surfaces.crosshair_red, surfaces.marker_red, red_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, red_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 2 : {
            ArmyColorDependentMisc yellow_widgets(surfaces.crosshair_yellow, surfaces.marker_yellow, yellow_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, yellow_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            }
            break;
            case 3 : {
            ArmyColorDependentMisc green_widgets(surfaces.crosshair_green, surfaces.marker_green, green_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, green_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            // worm_army_color = Green;
            }
            break;
            default: {

            }
            ArmyColorDependentMisc orange_widgets(surfaces.crossharir_purple, surfaces.marker_purple, orange_color);
            std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, orange_widgets, surfaces, renderer, bkgrnd);
            this->worms_map[worm_snpsht.id] = worm;
            // worm_army_color = Orange;
            break;
        }
        // std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, color_map, surfaces, renderer, bkgrnd);
        // this->worms_map[worm_snpsht.id] = worm;
        std::cout << "worm_map constructor, worm_id == " << +worm_snpsht.id << std::endl;
    }
    update_camera(1,1,true);
}

void Match::update_from_snapshot(Snapshot& snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    if (turn_time != (snpsht.turn_time_and_worm_turn.turn_time/FPS)) {
        turn_time = snpsht.turn_time_and_worm_turn.turn_time/FPS;
        camera.update_turn_time_text(turn_time);    
    }
    try {
        for (std::map<char,std::shared_ptr<Projectile>>::iterator it = projectiles_map.begin(); it != projectiles_map.end();) {
            std::cout << "Inside proj destroyer\n";
            if (it->second->get_proj_state() == EXPLODED) {
                std::cout << "Found proj exploded\n";
                Target new_target;
                if (get_next_target(new_target)) {
                    camera.update(new_target);
                } else {
                new_target = {
                    PlayerType,
                    -1,
                    -1,
                    it->second->get_proj_x() * RESOLUTION_MULTIPLIER,
                    it->second->get_proj_y() * RESOLUTION_MULTIPLIER
                };
                camera.update(new_target);
                }
                it = projectiles_map.erase(it);
            } else {
                ++it;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception in proj snapshot: " << e.what() << "\n";
    } catch (...) {
        std::cout << "ERROR NOT FOUND\n";
    }
    std::cout << "Before reading proj snapshot\n";
    for (auto& projectile_snpsht : snpsht.projectiles) {
        std::cout << "inside proj snapshot\n";
        if (projectiles_map.find(projectile_snpsht.id) == projectiles_map.end() or projectiles_map.count(projectile_snpsht.id) == 0) {
            std::cout << "Not found proj from snapshot in map\n";
            std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(projectile_snpsht, surfaces, renderer);
            this->projectiles_map[projectile_snpsht.id] = projectile;
            std::cout << "proj_map constructor, proj_id == " << +projectile_snpsht.id << std::endl;
        } else {
            std::cout << "Found proj from snapshot in map --> update\n";
            projectiles_map.at(projectile_snpsht.id)->update_from_snapshot(projectile_snpsht);
        }
    }

    for (auto& worm_snpsht : snpsht.worms) { 
        worms_map.at(worm_snpsht.id)->update_from_snapshot(worm_snpsht);
    }
    if (worm_turn_id != snpsht.turn_time_and_worm_turn.worm_turn) {
        worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
        update_camera(1,1,true);
    } else {
        worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
        update_camera();
    }
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
    update_camera();
}

void Match::render(SDL2pp::Renderer& renderer) {
    bkgrnd->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->render_texts_and_widgets(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    for (std::map<char,std::shared_ptr<Projectile>>::iterator it = projectiles_map.begin(); it != projectiles_map.end(); it++) {
        it->second->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
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
        if(turn_worm_has_charging_weapon()) {
            charge_for_weapon += 1;
            if(charge_for_weapon == 100) {
                std::cout << "Sending ActionShoot in space pressed with charge: " << charge_for_weapon << std::endl;
                action = std::make_shared<ActionShooting>(charge_for_weapon, worm_turn_id);
                charge_for_weapon = 0;
                return true;
            }
            std::cout << "Inside space pressed with charge: " << charge_for_weapon << std::endl;
        }
    }
    return false;
}

bool Match::handle_space_button_release(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(turn_worm_has_charging_weapon()) {
            std::cout << "Sending ActionShoot in space release with charge: " << charge_for_weapon << std::endl;
            action = std::make_shared<ActionShooting>(charge_for_weapon, worm_turn_id);
            charge_for_weapon = 0;
            return true;
        }
        if(turn_worm_has_weapon()) {
            action = std::make_shared<ActionShooting>(0, worm_turn_id);
        }
    }
    return false;
}


void Match::handle_mouse_left_click(int mouse_x, int mouse_y) {
    if(is_turn_worm_in_my_army()) {
    //     if(is_turn_worm_aiming_weapon()) {
    //         //action = std::make_shared<ActionShoot>(worm_turn_id);
    //     }
    }
}

bool Match::handle_mouse_right_click(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_still() and turn_worm_has_weapon_to_aim()) {
            action = std::make_shared<ActionAim>(turn_worm_facing_left() ? LEFT : RIGHT, CENTER, worm_turn_id);
            return true;
        }
        std::cout << "no entre al aiming\n"
    }
    return false;
}

bool Match::handle_mouse_scroll_up(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_still()) {
            action = std::make_shared<ActionChangeWeapon>(SCROLL_UP, worm_turn_id);
            return true;
        }
    }
    return false;
}

bool Match::handle_mouse_scroll_down(std::shared_ptr<Action>& action) {
    if(is_turn_worm_in_my_army()) {
        if(is_turn_worm_still()) {
            action = std::make_shared<ActionChangeWeapon>(SCROLL_DOWN, worm_turn_id);
            return true;
        }
    }
    return false;
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

bool Match::turn_worm_has_weapon() {
    return worms_map.at(worm_turn_id)->has_weapon();
}

bool Match::turn_worm_has_weapon_to_aim() {
    return worms_map.at(worm_turn_id)->has_weapon_to_aim();
}

bool Match::turn_worm_has_charging_weapon() {
    return worms_map.at(worm_turn_id)->has_charging_weapon();
}

bool Match::is_turn_worm_aiming_weapon() {
    return worms_map.at(worm_turn_id)->get_worm_state() == AIMING;
}