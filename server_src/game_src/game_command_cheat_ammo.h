#include "game_command.h"

#ifndef CHEAT_AMMO_COMMAND_H
#define CHEAT_AMMO_COMMAND_H
class CheatAmmoCommand: public GameCommand {
    public:
    CheatAmmoCommand(char id);
    ~CheatAmmoCommand();
    void execute(Game& game) override;

};

#endif  // CHEAT_LIFE_COMMAND_H