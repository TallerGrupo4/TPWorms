#include "game_command_exit.h"

ExitCommand::ExitCommand(char army_id) : GameCommand(), army_id(army_id) {}

ExitCommand::~ExitCommand() {}

void ExitCommand::execute(Game& game) { game.remove_player(army_id); } 

