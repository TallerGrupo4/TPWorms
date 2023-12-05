#include <memory>

#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


class GameCommand {
protected:
    // Make this private and add a getter
    char id_worm = -1;
    int direction;

public:
    explicit GameCommand(char id = -1, int direction = 0): id_worm(id), direction(direction) {}
    ~GameCommand() = default;

    char get_worm_id() { return id_worm; }

    int get_direction() { return direction; }

    void virtual execute(Game& game) { return; }
};


#endif  // GAME_COMMAND_H
