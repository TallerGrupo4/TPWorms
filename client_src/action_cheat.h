#ifndef ACTION_CHEAT_H
#define ACTION_CHEAT_H

#include "action.h"

class ActionCheat: public Action {
protected:
    Cheats cheat;

public:
    int send(Socket& socket, bool& was_closed) override {
        int ret;
        socket.sendall(&worm_id, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        socket.sendall(&type, 1, &was_closed);
        if (was_closed)
            return WAS_CLOSED;
        ret = socket.sendall(&cheat, 1, &was_closed);
        if (was_closed || ret != 1)
            return WAS_CLOSED;
        return ret;
    }
    ActionCheat(Cheats cheat, uint8_t worm_id): Action(CHEAT, 0, worm_id), cheat(cheat) {}
    ~ActionCheat() = default;
};

class ActionCheatExtraLife: public ActionCheat {
public:
    explicit ActionCheatExtraLife(uint8_t worm_id = 0): ActionCheat(EXTRA_LIFE, worm_id) {}
    ~ActionCheatExtraLife() = default;
};

class ActionCheatExtraAmmo: public ActionCheat {
public:
    explicit ActionCheatExtraAmmo(uint8_t worm_id = 0): ActionCheat(EXTRA_AMMO, worm_id) {}
    ~ActionCheatExtraAmmo() = default;
};

class ActionExtraTurnTime: public ActionCheat {
public:
    explicit ActionExtraTurnTime(uint8_t worm_id = 0): ActionCheat(EXTRA_TURN_TIME, worm_id) {}
    ~ActionExtraTurnTime() = default;
};

class ActionExtraShooting: public ActionCheat {
public:
    explicit ActionExtraShooting(uint8_t worm_id = 0): ActionCheat(EXTRA_SHOOTING, worm_id) {}
    ~ActionExtraShooting() = default;
};

#endif  // ACTION_CHEAT_H
