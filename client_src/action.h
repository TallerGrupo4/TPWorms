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
public:
    // char code = -1;
    // uint8_t number_of_players = 0;
    // uint match_id = 0;

    char id_worm = -1;
    char movement_x = 0;
    char type;

    Action(char type = -1) : type(type) {};
    ~Action() = default;
    
    // It should be const socket
    virtual int send(Socket& socket, bool& was_closed) {
        return 0;
    };

};

// Create a class for each action

class ActionStart : public Action {
public:
    int send(Socket& socket, bool& was_closed) override {
        char code[1] = {START};
        int ret = socket.sendall(code, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        return ret;
    };
    ActionStart() : Action(START) {};
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
        char id_worm[1] = {this->id_worm};
        ret = socket.sendall(id_worm, 1, &was_closed);
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
    ActionMov(char id_worm, char movement_x) : Action(MOV) {
        this->id_worm = id_worm;
        this->movement_x = movement_x;
    };
    ~ActionMov() = default;
};

#endif // ACTION_H
