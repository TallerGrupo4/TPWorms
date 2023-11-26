#include "game_command_jump.h"


int JumpCommand::get_direction() { return direction; }

JumpCommand::JumpCommand(char id, int direction): GameCommand(id, direction) {}

JumpCommand::~JumpCommand() {}

void JumpCommand::execute(Game& game) { game.jump_player(id_worm, direction); }

