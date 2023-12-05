#include <cstdint>
#include <string>

#include <netinet/in.h>
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
    explicit Action(char type = -1, char movement_x = 0, uint8_t worm_id = 0):
            type(type), movement_x(movement_x), worm_id(worm_id) {}
    ~Action() = default;

    virtual int send(Socket& socket, bool& was_closed) { return 0; }
    char get_type() { return type; }
    char get_movement_x() { return movement_x; }
    uint8_t get_worm_id() { return worm_id; }
};

#endif  // ACTION_H
