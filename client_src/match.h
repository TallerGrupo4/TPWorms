#ifndef MATCH_H
#define MATCH_H

#include <map>
#include <chrono>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "worm.h"
#include "background.h"
#include "surfaces.h"

class Match {
private:

    Background bkgrnd;
    std::map<char,Worm> worms_map;
    //Worm actual_worm; //Camera

public:
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    explicit Match();
    void update(Snapshot snpsht, int);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // MATCH_H