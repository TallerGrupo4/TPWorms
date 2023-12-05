#ifndef ACTION_CHANGE_WEAPON_H
#define ACTION_CHANGE_WEAPON_H

#include "action.h"

class ActionChangeWeapon: public Action {
private:
    char scroll_direction;

public:
    explicit ActionChangeWeapon(char scroll_direction, uint8_t worm_id = 0):
            Action(CHANGE_TOOL, 0, worm_id), scroll_direction(scroll_direction) {}

    int send(Socket& socket, bool& was_closed) override {
        int ret;
        socket.sendall(&worm_id, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        socket.sendall(&type, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        ret = socket.sendall(&scroll_direction, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        return ret;
    }

    ~ActionChangeWeapon() = default;
};

#endif  // ACTION_CHANGE_WEAPON_H
