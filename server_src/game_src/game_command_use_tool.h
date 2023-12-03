#include "game_command.h"

#ifndef GAME_COMMAND_USE_TOOL_H
#define GAME_COMMAND_USE_TOOL_H

class UseToolCommand: public GameCommand {
    int potency;
    float pos_x;
    float pos_y;
    int timer;

    public:
    UseToolCommand(int id, int potency, float pos_x , float pos_y, int timer);
    ~UseToolCommand();
    void execute(Game& game) override;

    int get_potency();

    float get_pos_x();

    float get_pos_y();
};


#endif  // __GAME_COMMAND_USE_TOOL_H
