#include "game_command.h"

#ifndef CHEAT_LIFE_COMMAND_H
#define CHEAT_LIFE_COMMAND_H
class CheatLifeCommand: public GameCommand {
public:
    explicit CheatLifeCommand(char id);
    ~CheatLifeCommand();
    void execute(Game& game) override;
};

#endif  // CHEAT_LIFE_COMMAND_H
