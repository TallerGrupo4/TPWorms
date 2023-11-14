#ifndef WORM_H
#define WORM_H

#include <chrono>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "surfaces.h"
#include "Animation.h"

class Worm {
public:
    //Worm(SDL2pp::Texture& texture, bool lookingleft, bool orientation_horizontal);
    Worm(WormSnapshot worm_snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer);
    ~Worm();
    void update(WormSnapshot worm_snpsht, std::chrono::duration<double> dt);
    void render(SDL2pp::Renderer& renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    bool is_same_id(char id_to_check);

private:
    Animation walking_an;
    bool facing_left;
    bool moving;
    float angle;
    char id;
    int health_points;
    int max_health;
    int state;
    int weapon;
    int x;
    int y;
};

#endif  // WORM_H