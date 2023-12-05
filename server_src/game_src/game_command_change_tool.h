#include "game_command.h"

#ifndef CHANGE_TOOL_COMMAND_H
#define CHANGE_TOOL_COMMAND_H

class ChangeToolCommand: public GameCommand {
public:
    ChangeToolCommand(char id, char tool);
    ~ChangeToolCommand();
    void execute(Game& game) override;
};


#endif  // GAME_COMMAND_H
