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
public: // Protected and make getters

    char movement_x = 0;
    char type;

    Action(char type = -1) : type(type) {};
    ~Action() = default;
    
    // It should be const socket
    virtual bool is_exit() {
        return false;
    };
    virtual int send(Socket& socket, bool& was_closed) {
        return 0;
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

class ActionStart : public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        char code[1] = {ACTION_START};
        int ret = socket.sendall(code, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        return ret;
    };
    ActionStart() : Action(ACTION_START) {};
    ~ActionStart() = default;
};

class ActionMov : public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        char code[1] = {MOV};
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
    ActionMov( char movement_x) : Action(MOV) {
        this->movement_x = movement_x;
    };
    ~ActionMov() = default;
};

// class ActionMovLeft : public Action {
// public:
//     int send(Socket& socket, bool& was_closed) override {
//         char code[1] = {MOV};
//         int ret = socket.sendall(code, 1, &was_closed);
//         if (ret < 0) {
//             return SOCKET_FAILED;
//         }
//         if (was_closed) return WAS_CLOSED;
//         char movement_x[1] = {this->movement_x};
//         ret = socket.sendall(movement_x, 1, &was_closed);
//         if (ret < 0) {
//             return SOCKET_FAILED;
//         }
//         return ret;
//     }
//     ActionMovLeft() : Action(LEFT) {
//         this->movement_x = movement_x;
//     };
//     ~ActionMovLeft() = default;
// };

#endif // ACTION_H
