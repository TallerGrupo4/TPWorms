#include "Player.h"

Player::Player(SDL2pp::Texture &texture, bool lookingleft, bool orientation_horizontal): an(texture, orientation_horizontal), sprites_lookingleft(lookingleft), facingLeft(lookingleft), moving(false), x(300), y(300) {}

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? (sprites_lookingleft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) : (sprites_lookingleft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    an.render(renderer, SDL2pp::Rect(x, y, 200, 200), flip);
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() {
    moving = false;
}
