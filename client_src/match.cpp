#include "match.h"

Match::Match() {}

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : bkgrnd(snpsht.platforms, surfaces, renderer) {
    for (WormSnapshot worm_snpsht : snpsht.worms){
        Worm worm(worm_snpsht, surfaces, renderer);
        this->worms.push_back(worm);
    }
}

void Match::update(Snapshot snpsht, int iter) {
    for (WormSnapshot worm_snpsht : snpsht.worms) {
        worms_map.at(worm_snpsht.id).update(worm_snpsht, iter);
    }  
    
    
    for (Worm worm : this->worms) { // {w1 , w2 , w3} for each w.update()
        for (WormSnapshot worm_snpsht : snpsht.worms) {
            if(worm.is_same_id(worm_snpsht.id)) {
                worm.update(worm_snpsht, iter);
                break;
            }
        }        
    }
}
void Match::render(SDL2pp::Renderer& renderer) {
    bkgrnd.render(renderer);
    for (Worm worm : this->worms) {
        worm.render(renderer);    
    }
}