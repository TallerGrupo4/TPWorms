#include <cstdint>
#include <string>
#include <sys/types.h>

#include "../common_src/constants.h"

#ifndef TESTING
#include "../common_src/socket.h"
#else
#include "../common_src/dummy_socket.h"
#endif

#ifndef ACTION_H
#define ACTION_H

class Action {
protected:
    char type;
    char movement_x;
    uint8_t worm_id;

public:

    Action(char type = -1, char movement_x = 0, uint8_t worm_id = 0) : type(type), movement_x(movement_x), worm_id(worm_id) {};
    ~Action() = default;

    virtual int send(Socket& socket, bool& was_closed) {
        return 0;
    };
    char get_type() {
        return type;
    };
    char get_movement_x() {
        return movement_x;
    };
    uint8_t get_worm_id() {
        return worm_id;
    };

};




class ActionMov : public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        uint8_t worm_id[1] = {this->worm_id};
        int ret = socket.sendall(worm_id, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        char code[1] = {type};
        ret = socket.sendall(code, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        char movement_x[1] = {this->movement_x};
        ret = socket.sendall(movement_x, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        return ret;
    }
    ActionMov(char type, char movement_x, uint8_t worm_id) : Action(type, movement_x, worm_id) {};
    ~ActionMov() = default;
};

class ActionMovLeft : public ActionMov {
public:
    ActionMovLeft(uint8_t worm_id = 0) : ActionMov(MOV, LEFT, worm_id) {};
    ~ActionMovLeft() = default;
};

class ActionMovRight : public ActionMov {
public:
    ActionMovRight(uint8_t worm_id = 0) : ActionMov(MOV, RIGHT, worm_id) {};
    ~ActionMovRight() = default;
};

class ActionJump : public ActionMov {
public:
    ActionJump(uint8_t worm_id = 0) : ActionMov(JUMP, FOWARD, worm_id) {};
    ~ActionJump() = default;
};

class ActionBackflip: public ActionMov {
public:
    ActionBackflip(uint8_t worm_id = 0) : ActionMov(JUMP, BACKWARD, worm_id) {};
    ~ActionBackflip() = default;
};

#endif // ACTION_H
