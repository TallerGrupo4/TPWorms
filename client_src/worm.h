#ifndef WORM_H
#define WORM_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common_src/snapshot.h"
#include "../common_src/constants.h"
#include "constantes_cliente.h"
#include "worm_animations.h"
#include "surfaces.h"
#include "worm_texts.h"
#include "Animation.h"
#include "background.h"

class Worm {
public:
    //Worm(SDL2pp::Texture& texture, bool lookingleft, bool orientation_horizontal);
    Worm(WormSnapshot worm_snpsht, int worm_width, int worm_height, SDL_Color worm_color, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, std::shared_ptr<Background> bkgrnd);
    ~Worm();
    void update_from_snapshot(WormSnapshot& worm_snpsht);
    void update_from_iter(int iter);
    void render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    int get_worm_state();
    int get_worm_x();
    int get_worm_y();
    bool worm_facing_left();
    char get_army_id();
private:
    std::shared_ptr<Background> bkgrnd;
    WormAnimations worm_an;
    bool facing_left;
    bool moving;
    int angle;
    char id;
    int health_points;
    int max_health;
    int state;
    TOOLS weapon;
    int aiming_angle;
    int x;
    int y;
    int width;
    int height;
    char army_id;
    WormSpecificTexts worm_texts;
};

#endif  // WORM_H