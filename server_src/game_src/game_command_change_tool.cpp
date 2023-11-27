#include "game_command_change_tool.h"

ChangeToolCommand::ChangeToolCommand(char id_worm , char direction) : GameCommand(id_worm , direction) {}

ChangeToolCommand::~ChangeToolCommand() {}

void ChangeToolCommand::execute(Game& game) {
    game.player_change_tool(id_worm, direction);
}