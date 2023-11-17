#include "worm.h"

Worm::Worm(WormSnapshot worm_snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, Background& bkgrnd) : 
    bkgrnd(bkgrnd),
    walking_an(SDL2pp::Texture(renderer, surfaces.walking_worm), false),
    facing_left(worm_snpsht.direction == 0 ? true : false),
    //facing_left(worm_snpsht.direction),
    moving(false),
    angle(worm_snpsht.angle),
    id(worm_snpsht.id),
    health_points(worm_snpsht.health),
    max_health(worm_snpsht.max_health),
    state(worm_snpsht.state),
    weapon(worm_snpsht.weapon),
    x(worm_snpsht.pos_x),
    y(worm_snpsht.pos_y) {}


// Worm::Worm(SDL2pp::Texture& texture, bool lookingleft, bool orientation_horizontal):
//         an(texture, orientation_horizontal),
//         sprites_lookingleft(lookingleft),
//         facingLeft(lookingleft),
//         moving(false),
//         x(300),
//         y(300) {

//         }

Worm::~Worm() {}

bool Worm::is_same_id(char id_to_check) {
    return id_to_check == id;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Worm::update_from_snapshot(WormSnapshot worm_snpsht) {
    angle = worm_snpsht.angle;
    facing_left = (worm_snpsht.direction == 0 ? true : false);
    health_points = worm_snpsht.health;
    state = worm_snpsht.state;
    y = worm_snpsht.pos_y;
    x = worm_snpsht.pos_x;
    if (state == 0) {
        walking_an.update_once();
        // if (facing_left)
        //     x -= 10;
        // else
        //     x += 10;
    }
}

void Worm::render(SDL2pp::Renderer& renderer) {
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    std::cout << "x: " << x << " y: " << y << std::endl;
    int top_left_x = (x*PIX_PER_METER)-WORM_CENTER + (int)(bkgrnd.get_map_width()/2);
    int top_left_y = (y*PIX_PER_METER)-WORM_CENTER + (int)(bkgrnd.get_map_height()/2);
    walking_an.render(renderer, SDL2pp::Rect(top_left_x, top_left_y, 200, 200), flip);
}

void Worm::moveRigth() {
    moving = true;
    facing_left = false;
}

void Worm::moveLeft() {
    moving = true;
    facing_left = true;
}

void Worm::stopMoving() { moving = false; }
