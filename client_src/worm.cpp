#include "worm.h"

Worm::Worm(WormSnapshot worm_snpsht, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, std::shared_ptr<Background> bkgrnd) : 
    bkgrnd(bkgrnd),
    walking_an(renderer,surfaces.walking_worm, false),
    facing_left(worm_snpsht.direction == LEFT ? true : false),
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

int Worm::get_worm_state() {
    return this->state;
}

int Worm::get_worm_x() {
    return this->x;
}

int Worm::get_worm_y() {
    return this->y;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Worm::update_from_snapshot(WormSnapshot& worm_snpsht) {
    angle = worm_snpsht.angle;
    facing_left = (worm_snpsht.direction == LEFT ? true : false);
    health_points = worm_snpsht.health;
    state = worm_snpsht.state;
    //std::cout << "update_from_snapshot nueva pos_y snap: " << worm_snpsht.pos_y << std::endl;
    //std::cout << "update_from_snapshot nueva pos_x snap: " << worm_snpsht.pos_x << std::endl;
    y = worm_snpsht.pos_y;
    x = worm_snpsht.pos_x;
    if (state == MOVING) {
        walking_an.update_once();
    }
}

void Worm::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    SDL_RendererFlip flip = facing_left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    std::cout << "x worm: " << x << " y worm: " << y << std::endl;
    int top_left_x = (x-WORM_CENTER_X)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_left_y = (y+WORM_CENTER_Y)*(-1)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;
    std::cout << "top_left_x: " << top_left_x << " top_left_y: " << top_left_y << std::endl;
    walking_an.render(renderer, SDL2pp::Rect(top_left_x, top_left_y, WORM_CENTER_X*2*RESOLUTION_MULTIPLIER,
                      WORM_CENTER_Y*2*RESOLUTION_MULTIPLIER),
                      flip,
                      WORM_WALK_LEFT_OFFSET,
                      WORM_WALK_RIGHT_OFFSET,
                      WORM_WALK_ABOVE_OFFSET,
                      WORM_WALK_BELLOW_OFFSET);
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
