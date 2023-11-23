#include <string>

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
public:

    Action(char type = -1, char movement_x = 0) : type(type), movement_x(movement_x) {};
    ~Action() = default;
    
    // It should be const socket
    virtual bool is_exit() {
        return false;
    };
    virtual int send(Socket& socket, bool& was_closed) {
        return 0;
    };
    char get_type() {
        return type;
    };
    char get_movement_x() {
        return movement_x;
    };

};

// Create a class for each action

class ActionExit : public Action {
public:
    bool is_exit() override {
        return true;
    };
    ActionExit() : Action(ACTION_EXIT) {};
    ~ActionExit() = default;
};


class ActionMov : public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        char code[1] = {type};
        int ret = socket.sendall(code, 1, &was_closed);
        if (ret < 0) {
            return SOCKET_FAILED;
        }
        if (was_closed) return WAS_CLOSED;
        char movement_x[1] = {this->movement_x};
        ret = socket.sendall(movement_x, 1, &was_closed);
        if (ret < 0) {
            return SOCKET_FAILED;
        }
        return ret;
    }
    ActionMov(char type, char movement_x) : Action(type, movement_x) {};
    ~ActionMov() = default;
};

class ActionMovLeft : public ActionMov {
public:
    ActionMovLeft() : ActionMov(MOV, LEFT) {};
    ~ActionMovLeft() = default;
};

class ActionMovRight : public ActionMov {
public:
    ActionMovRight() : ActionMov(MOV, RIGHT) {};
    ~ActionMovRight() = default;
};

class ActionJumpRight : public ActionMov {
public:
    ActionJumpRight() : ActionMov(JUMP, RIGHT) {};
    ~ActionJumpRight() = default;
};

class ActionJumpLeft : public ActionMov {
public:
    ActionJumpLeft() : ActionMov(JUMP, LEFT) {};
    ~ActionJumpLeft() = default;
};
    

#endif // ACTION_H
