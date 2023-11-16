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
    std::map<char,std::shared_ptr<Worm>> worms_map;
    //Worm actual_worm; //Camera

public:
    explicit Match(Snapshot snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    explicit Match();
    void update_from_snapshot(Snapshot snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer);
};

#endif  // MATCH_H