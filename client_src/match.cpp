#include "match.h"
#include <iostream>
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    // std::cout << "Antes de crear el background" << std::endl;
    bkgrnd = std::make_shared<Background>(snpsht.platforms, snpsht.map_dimensions.width, snpsht.map_dimensions.height, surfaces, renderer);
    // std::cout << "Cant de gusanos: "<< (int)snpsht.worms.size() << std::endl;
    for (WormSnapshot worm_snpsht : snpsht.worms){
        // std::cout << "Angulo del gusano: " << worm_snpsht.angle << std::endl;
        // std::cout << "Direccion del gusano: " << (int)worm_snpsht.direction << std::endl;
        // std::cout << "Vida del gusano: " << worm_snpsht.health << std::endl;
        // std::cout << "ID del gusano: " << (int)worm_snpsht.id << std::endl;
        // std::cout << "Vida Max del gusano: " << worm_snpsht.max_health << std::endl;
        // std::cout << "Pos X del gusano: " << worm_snpsht.pos_x << std::endl;
        // std::cout << "Pos Y del gusano: " << worm_snpsht.pos_y << std::endl;
        // std::cout << "Estado del gusano: " << worm_snpsht.state << std::endl;
        // std::cout << "Arma del gusano: " << worm_snpsht.weapon << std::endl;
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, snpsht.map_dimensions.worm_width, snpsht.map_dimensions.worm_height, surfaces, renderer, bkgrnd);
        this->worms_map[worm_snpsht.id] = worm;
        std::cout << "worm_map constructor, worm_id == " << +worm_snpsht.id << std::endl;
        // this->worms.push_back(worm);
    }
}

void Match::update_from_snapshot(Snapshot& snpsht) {
    // Now you can access the turn_time and worm_turn by doing: snpsht.turn_time_and_worm_turn.turn_time and snpsht.turn_time_and_worm_turn.worm_turn
    for (auto& worm_snpsht : snpsht.worms) {
        worms_map.at(worm_snpsht.id)->update_from_snapshot(worm_snpsht);
    }
    update_camera();
    
    // for (Worm worm : this->worms) { // {w1 , w2 , w3} for each w.update()
    //     for (WormSnapshot worm_snpsht : snpsht.worms) {
    //         if(worm.is_same_id(worm_snpsht.id)) {
    //             worm.update(worm_snpsht, iter);
    //             break;
    //         }
    //     }        
    // }
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

void Match::update_camera(int camera_offset_x, int camera_offset_y, bool center_camera) { 
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
        if(get_next_target(new_target)) {
            camera.update(new_target);
            break;
        }
        if (((camera_offset_x != 0) and (camera_offset_y != 0)) or center_camera) {
            new_target = {
                PlayerType,
                -1,
                -1,
                camera_offset_x,
                camera_offset_y
            };
            camera.update(new_target);
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
    
    // for (std::shared_ptr<Worm> worm : worms_map) {
    //     worm.render(renderer);    
    // }
}