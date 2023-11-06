#ifndef WORM_H
#define WORM_H

//#include "SDL2pp.hh"
#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
class Player {
public:
    Player(SDL2pp::Texture& texture, bool lookingleft, bool orientation_horizontal);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer& renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool sprites_lookingleft;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif  // WORM_H