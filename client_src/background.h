#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <list>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "surfaces.h"
#include "beam.h"

class Background {
private:
    std::list<Beam> beams;
    //SDL2pp::Texture bkgrnd_image;
    int width;
    int height;

public:
    explicit Background(std::vector<PlatformSnapshot> platforms, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
};

#endif  // BACKGROUND_H