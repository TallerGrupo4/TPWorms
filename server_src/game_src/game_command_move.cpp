#include "game_command_move.h"


MoveCommand::MoveCommand(char id, int direction): GameCommand(id, direction) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute(Game& game) {
    game.move_player(id_worm, direction);
}

int MoveCommand::get_direction() {
    return direction;
}
