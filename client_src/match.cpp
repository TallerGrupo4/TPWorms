#include "match.h"
#include <iostream>
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    // std::cout << "Antes de crear el background" << std::endl;
    bkgrnd = std::make_shared<Background>(snpsht.platforms, snpsht.map_dimensions.width, snpsht.map_dimensions.height, surfaces, renderer);
    my_army_id = snpsht.my_army.begin()->first;
    std::cout << "my_army_id : " << +my_army_id << std::endl;
    worm_turn_id = snpsht.turn_time_and_worm_turn.worm_turn;
    std::cout << "worm_turn_id : " << +worm_turn_id << std::endl;
    turn_time = snpsht.turn_time_and_worm_turn.turn_time;
    // std::cout << "Cant de gusanos: "<< (int)snpsht.worms.size() << std::endl;
    for (WormSnapshot worm_snpsht : snpsht.worms){
        SDL_Color worm_color;
        switch (worm_snpsht.team_id) {
            case 0 :
            worm_color = BLUE;
            break;
            case 1 :
            worm_color = RED;
            break;
            case 2 :
            worm_color = YELLOW;
            break;
            case 3 :
            worm_color = GREEN;
            break;
            default:
            worm_color = ORANGE;
            break;
        }
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, worm_color, surfaces, renderer, bkgrnd);
        this->worms_map[worm_snpsht.id] = worm;
        std::cout << "worm_map constructor, worm_id == " << +worm_snpsht.id << std::endl;
    }
}

void Match::update_from_snapshot(Snapshot& snpsht) {
    // Now you can access the turn_time and worm_turn by doing: snpsht.turn_time_and_worm_turn.turn_time and snpsht.turn_time_and_worm_turn.worm_turn
    turn_time = snpsht.turn_time_and_worm_turn.turn_time;
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
        if(it->second->get_worm_state() != STILL) {
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
        if(target_worm->get_worm_state() != STILL) {
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
        /* code */
        break;
    }
}

void Match::update_from_iter(int iter) {
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->update_from_iter(iter);
    }
    update_camera();
}

void Match::render(SDL2pp::Renderer& renderer) {
    bkgrnd->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->render(renderer, this->camera.get_offset_x(), this->camera.get_offset_y());
    }
    this->camera.render(renderer);
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