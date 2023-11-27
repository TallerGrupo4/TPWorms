#include "game_command.h"

#ifndef AIM_COMMAND_H
#define AIM_COMMAND_H

class AimCommand : public GameCommand {
    char look_direction_x;
    char look_direction_y;

    public:
    AimCommand(char look_direction_x, char look_direction_y, char worm_id);
    ~AimCommand() {};
    void execute(Game& game) override;

};


#endif  // AIM_COMMAND_H