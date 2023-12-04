#include "game_command.h"

#ifndef CHEAT_TURN_COMMAND_H
#define CHEAT_TURN_COMMAND_H

class CheatTurnCommand: public GameCommand {
    public:
    CheatTurnCommand(char id);
    ~CheatTurnCommand();
    void execute(Game& game) override;

};

#endif  // CHEAT_TURN_COMMAND_H