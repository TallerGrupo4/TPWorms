#ifndef ACTION_AIM_H
#define ACTION_AIM_H

#include "action.h"

class ActionAim: public Action {
private:
    char look_direction_x;
    char look_direction_y;

public:
    ActionAim(char look_direction_x, char look_direction_y, uint8_t worm_id = 0):
            Action(AIM, 0, worm_id),
            look_direction_x(look_direction_x),
            look_direction_y(look_direction_y) {}

    int send(Socket& socket, bool& was_closed) override {
        int ret;
        socket.sendall(&this->worm_id, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        socket.sendall(&type, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        socket.sendall(&this->look_direction_x, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        ret = socket.sendall(&this->look_direction_y, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        return ret;
    }

    ~ActionAim() = default;
};

#endif  // ACTION_AIM_H
