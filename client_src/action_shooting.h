#ifndef ACTION_SHOOTING_H
#define ACTION_SHOOTING_H

#include "action.h"


class ActionShooting: public Action {
private:
    int potency;
    int position_x = 0;
    int position_y = 0;
    int timer = 0;

public:
    explicit ActionShooting(int potency, uint8_t worm_id = 0, int timer = 0, int position_x = 0,
                            int position_y = 0):
            Action(SHOOT, 0, worm_id),
            potency(potency),
            position_x(position_x),
            position_y(position_y),
            timer(timer) {}

    int send(Socket& socket, bool& was_closed) override {
        int ret;
        socket.sendall(&worm_id, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        socket.sendall(&type, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        int send_potency = htonl(potency);
        socket.sendall(&send_potency, 4, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        int send_position_x = htonl(position_x);
        socket.sendall(&send_position_x, 4, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        int send_position_y = htonl(position_y);
        socket.sendall(&send_position_y, 4, &was_closed);
        int send_timer = htonl(timer);
        ret = socket.sendall(&send_timer, 4, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        return ret;
    }

    ~ActionShooting() = default;
};

#endif  // ACTION_SHOOTING_H
