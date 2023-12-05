#include "game_command.h"

#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

class MoveCommand: public GameCommand {
public:
    int get_direction();
    MoveCommand(char id, int direction);
    ~MoveCommand();
    void execute(Game& game) override;
};

#endif  // MOVE_COMMAND_H
