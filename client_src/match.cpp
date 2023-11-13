#include "match.h"

Match::Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer) : bkgrnd(snpsht.platforms, surfaces, renderer) {
    for (WormSnapshot worm_snpsht : snpsht.worms){
        Worm worm(worm_snpsht, surfaces, renderer);
        this->worms.push_back(worm);
    }
}

void Match::update(Snapshot snpsht, std::chrono::duration<double>& dt) {
    for (Worm worm : this->worms) {
        for (WormSnapshot worm_snpsht : snpsht.worms) {
            if(worm.is_same_id(worm_snpsht.id)) {
                worm.update(worm_snpsht, dt);
                break;
            } 
        }        
    }
}
void Match::render(SDL2pp::Renderer& renderer) {
     
}