#include "game_command.h"

#ifndef __GAME_COMMAND_EXIT_H
#define __GAME_COMMAND_EXIT_H

class ExitCommand: public GameCommand {
    char army_id;

public:
    explicit ExitCommand(char army_id);
    ~ExitCommand();
    void execute(Game& game) override;
};

#endif  // __GAME_COMMAND_EXIT_H
