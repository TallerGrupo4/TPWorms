#include "match.h"
#include <iostream>
Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) {
    // std::cout << "Antes de crear el background" << std::endl;
    bkgrnd = std::make_shared<Background>(snpsht.platforms, snpsht.width, snpsht.height, surfaces, renderer);
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
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, surfaces, renderer, bkgrnd);
        std::cout << "worm_map constructor, worm_id == " << +worm_snpsht.id << std::endl;
        this->worms_map[worm_snpsht.id] = worm;
        // this->worms.push_back(worm);
    }
}

void Match::update_from_snapshot(Snapshot& snpsht) {
    for (auto& worm_snpsht : snpsht.worms) {
        worms_map.at(worm_snpsht.id)->update_from_snapshot(worm_snpsht);
    }
    
    
    // for (Worm worm : this->worms) { // {w1 , w2 , w3} for each w.update()
    //     for (WormSnapshot worm_snpsht : snpsht.worms) {
    //         if(worm.is_same_id(worm_snpsht.id)) {
    //             worm.update(worm_snpsht, iter);
    //             break;
    //         }
    //     }        
    // }
}

void Match::update_from_iter(int iter) {}

void Match::render(SDL2pp::Renderer& renderer) {
    bkgrnd->render(renderer);
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->render(renderer);
    }
    
    // for (std::shared_ptr<Worm> worm : worms_map) {
    //     worm.render(renderer);    
    // }
}