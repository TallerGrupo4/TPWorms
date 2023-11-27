#include <memory>
#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


class GameCommand {
protected:
    // Make this private and add a getter
    char id_worm = -1; 
    int direction;

public:
    GameCommand(char id = -1, int direction = 0): id_worm(id), direction(direction) {};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
};

class AimCommand : public GameCommand {
    char look_direction_x;
    char look_direction_y;

    public:
    AimCommand(char look_direction_x, char look_direction_y, char worm_id): GameCommand(worm_id), look_direction_x(look_direction_x), look_direction_y(look_direction_y) {};
    ~AimCommand() {};
    void execute(Game& game) override { game.player_aim(id_worm , look_direction_y, look_direction_x); }

};




#endif  // GAME_COMMAND_H