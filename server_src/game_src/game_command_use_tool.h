#include "game_command.h"

#ifndef GAME_COMMAND_USE_TOOL_H
#define GAME_COMMAND_USE_TOOL_H

class UseToolCommand: public GameCommand {
    int potency;
    float pos_x;
    float pos_y;

    public:
    UseToolCommand(int id, int potency, float pos_x , float pos_y);
    ~UseToolCommand();
    void execute(Game& game) override;

};


#endif  // __GAME_COMMAND_SHOOT_H