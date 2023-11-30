#ifndef ACTION_SHOOTING_H
#define ACTION_SHOOTING_H

#include "action.h"


class ActionShooting: public Action {
private:
    int potency;
    int position_x = 0;
    int position_y = 0;
public:
    ActionShooting(int potency, uint8_t worm_id = 0, int position_x = 0, int position_y = 0) : Action(SHOOT, 0, worm_id), potency(potency), position_x(position_x), position_y(position_y) {};

    int send(Socket& socket, bool& was_closed) override {
        uint8_t worm_id[1] = {this->worm_id};
        int ret = socket.sendall(worm_id, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        char code[1] = {type};
        ret = socket.sendall(code, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        int potency[1] = {this->potency};
        potency[0] = htonl(potency[0]);
        ret = socket.sendall(potency, 4, &was_closed);
        if (was_closed) return WAS_CLOSED;
        int position_x[1] = {this->position_x};
        position_x[0] = htonl(position_x[0]);
        ret = socket.sendall(position_x, 4, &was_closed);
        if (was_closed) return WAS_CLOSED;
        int position_y[1] = {this->position_y};
        position_y[0] = htonl(position_y[0]);
        ret = socket.sendall(position_y, 4, &was_closed);
        if (was_closed) return WAS_CLOSED;
        return ret;
    }

    ~ActionShooting() = default;
};

#endif //ACTION_SHOOTING_H
