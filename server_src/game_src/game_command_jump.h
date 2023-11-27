#include "game_command.h"

#ifndef JUMP_COMMAND_H
#define JUMP_COMMAND_H
class JumpCommand: public GameCommand {
    public:
    int get_direction();
    JumpCommand(char id, int direction);
    ~JumpCommand();
    void execute(Game& game) override;

};

#endif  // GAME_COMMAND_H