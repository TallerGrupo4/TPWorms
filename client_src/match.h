#ifndef MATCH_H
#define MATCH_H

#include <list>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "worm.h"
#include "background.h"
#include "surfaces.h"

class Match {
private:
    Background bkgrnd;
    std::list<Worm> worms;
    //Worm actual_worm; //Camera

public:
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    void update(Snapshot snpsht, std::chrono::duration<double>& dt);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // MATCH_H