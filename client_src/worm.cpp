#include "worm.h"

Worm::Worm(WormSnapshot worm_snpsht, int worm_width, int worm_height, SDL_Color worm_color, MatchSurfaces& surfaces, SDL2pp::Renderer& renderer, std::shared_ptr<Background> bkgrnd) : 
    bkgrnd(bkgrnd),
    worm_an(renderer, surfaces),
    facing_left(worm_snpsht.direction == LEFT ? true : false),
    moving(false),
    angle(worm_snpsht.angle),
    id(worm_snpsht.id),
    health_points(worm_snpsht.health),
    max_health(worm_snpsht.max_health),
    state(worm_snpsht.state),
    weapon(worm_snpsht.weapon),
    x(worm_snpsht.pos_x),
    y((-1)*worm_snpsht.pos_y),
    width(worm_width),
    height(worm_height),
    army_id(worm_snpsht.team_id),
    worm_texts(renderer, army_id, worm_color, id, health_points, max_health) {std::cout << "worm " << +id << " army_id: " << +army_id << std::endl;}


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

bool Worm::worm_facing_left() {
    return this->facing_left;
}

char Worm::get_army_id() {
    return this->army_id;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Worm::update_from_snapshot(WormSnapshot& worm_snpsht) {
    angle = worm_snpsht.angle;
    facing_left = (worm_snpsht.direction == LEFT ? true : false);
    health_points = worm_snpsht.health;
    worm_texts.update_health(health_points, max_health);
    state = worm_snpsht.state;
    //std::cout << "worm " << +worm_snpsht.id << " state: " << state << std::endl;
    //std::cout << "update_from_snapshot nueva pos_y snap: " << worm_snpsht.pos_y << std::endl;
    //std::cout << "update_from_snapshot nueva pos_x snap: " << worm_snpsht.pos_x << std::endl;
    y = (-1)*worm_snpsht.pos_y;
    x = worm_snpsht.pos_x;
    worm_an.update_from_snapshot(state, angle, facing_left);

    // if (state == MOVING) {
    //     walking_an.update_once();
    // }
}

void Worm::update_from_iter(int iter) {
    for (int i = 0; i < iter; i++) {

        worm_an.update_from_iter(state, angle, facing_left);
        // if (this->state == STILL) {
        //     still_1_an.update_once();
        // }
    }
}

void Worm::render(SDL2pp::Renderer& renderer, int camera_offset_x, int camera_offset_y) {
    //std::cout << "x worm: " << x << " y worm: " << y << std::endl;
    int top_left_x = (x-width/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalWidth()/2) - camera_offset_x;
    int top_left_y = (y-height/2)*RESOLUTION_MULTIPLIER + (int)(renderer.GetLogicalHeight()/2) - camera_offset_y;
    //std::cout << "top_left_x: " << top_left_x << " top_left_y: " << top_left_y << std::endl;
    
    worm_an.render(state, angle, renderer, SDL2pp::Rect(top_left_x, top_left_y, width*RESOLUTION_MULTIPLIER,
                        height*RESOLUTION_MULTIPLIER),
                        facing_left,
                        WORM_WALK_LEFT_OFFSET,
                        WORM_WALK_RIGHT_OFFSET,
                        WORM_WALK_ABOVE_OFFSET,
                        WORM_WALK_BELLOW_OFFSET);
    
    worm_texts.render(renderer, top_left_x + width*RESOLUTION_MULTIPLIER/2, top_left_y, top_left_y + height*RESOLUTION_MULTIPLIER);
}
