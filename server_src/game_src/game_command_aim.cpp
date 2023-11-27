#include "game_command_aim.h"

AimCommand::AimCommand(char look_direction_x, char look_direction_y, char worm_id): GameCommand(worm_id), look_direction_x(look_direction_x), look_direction_y(look_direction_y) {}

void AimCommand::execute(Game& game) { game.player_aim(id_worm , look_direction_y, look_direction_x); }
