#ifndef ACTION_MOV_H
#define ACTION_MOV_H

#include "action.h"

class ActionCheat : public Action {
protected:
    Cheats cheat;
public:
    int send(Socket& socket, bool& was_closed) override {
        uint8_t worm_id[1] = {this->worm_id};
        int ret = socket.sendall(worm_id, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        char code[1] = {type};
        ret = socket.sendall(code, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        Cheats cheat[1] = {this->cheat};
        ret = socket.sendall(cheat, 1, &was_closed);
        if (was_closed) return WAS_CLOSED;
        return ret;
    }
    ActionCheat(Cheats cheat, uint8_t worm_id) : Action(CHEAT, 0, worm_id), cheat(cheat) {};
    ~ActionCheat() = default;
};

class ActionCheatExtraLife : public ActionCheat {
public:
    ActionCheatExtraLife(uint8_t worm_id = 0) : ActionCheat(EXTRA_LIFE, worm_id) {};
    ~ActionCheatExtraLife() = default;
};

class ActionCheatExtraAmmo : public ActionCheat {
public:
    ActionCheatExtraAmmo(uint8_t worm_id = 0) : ActionCheat(EXTRA_AMMO, worm_id) {};
    ~ActionCheatExtraAmmo() = default;
};

class ActionExtraTurnTime : public ActionCheat {
public:
    ActionExtraTurnTime(uint8_t worm_id = 0) : ActionCheat(EXTRA_TURN_TIME, worm_id) {};
    ~ActionExtraTurnTime() = default;
};

class ActionExtraShooting: public ActionCheat {
public:
    ActionExtraShooting(uint8_t worm_id = 0) : ActionCheat(EXTRA_SHOOTING, worm_id) {};
    ~ActionExtraShooting() = default;
};

#endif //ACTION_MOV_H
