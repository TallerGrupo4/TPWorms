#ifndef ACTION_MOV_H
#define ACTION_MOV_H

#include "action.h"

class ActionMov: public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        uint8_t worm_id[1] = {this->worm_id};
        int ret;
        socket.sendall(worm_id, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        char code[1] = {type};
        socket.sendall(code, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        char movement_x[1] = {this->movement_x};
        ret = socket.sendall(movement_x, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        return ret;
    }
    ActionMov(char type, char movement_x, uint8_t worm_id): Action(type, movement_x, worm_id) {}
    ~ActionMov() = default;
};

class ActionMovLeft: public ActionMov {
public:
    explicit ActionMovLeft(uint8_t worm_id = 0): ActionMov(MOV, LEFT, worm_id) {}
    ~ActionMovLeft() = default;
};

class ActionMovRight: public ActionMov {
public:
    explicit ActionMovRight(uint8_t worm_id = 0): ActionMov(MOV, RIGHT, worm_id) {}
    ~ActionMovRight() = default;
};

class ActionJump: public ActionMov {
public:
    explicit ActionJump(uint8_t worm_id = 0): ActionMov(JUMP, FORWARD, worm_id) {}
    ~ActionJump() = default;
};

class ActionBackflip: public ActionMov {
public:
    explicit ActionBackflip(uint8_t worm_id = 0): ActionMov(JUMP, BACKWARD, worm_id) {}
    ~ActionBackflip() = default;
};

#endif  // ACTION_MOV_H
