#include "match.h"

Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : bkgrnd(snpsht.platforms, surfaces, renderer) {
    for (WormSnapshot worm_snpsht : snpsht.worms){
        std::shared_ptr<Worm> worm = std::make_shared<Worm>(worm_snpsht, surfaces, renderer);
        this->worms_map[worm_snpsht.id] = worm;
        // this->worms.push_back(worm);
    }
}

void Match::update_from_snapshot(Snapshot snpsht) {
    for (WormSnapshot worm_snpsht : snpsht.worms) {
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
    bkgrnd.render(renderer);
    for (std::map<char,std::shared_ptr<Worm>>::iterator it = worms_map.begin(); it != worms_map.end(); it++) {
        it->second->render(renderer);
    }
    
    // for (std::shared_ptr<Worm> worm : worms_map) {
    //     worm.render(renderer);    
    // }
}