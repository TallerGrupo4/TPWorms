#include "game_command.h"

#ifndef CHEAT_SHOOT_COMMAND_H
#define CHEAT_SHOOT_COMMAND_H

class CheatShootCommand: public GameCommand {
    public:
    CheatShootCommand(char id);
    ~CheatShootCommand();
    void execute(Game& game) override;

};

#endif  // CHEAT_SHOOT_COMMAND_H