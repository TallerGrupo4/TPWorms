#include "game_command_cheat_turn.h"

CheatTurnCommand::CheatTurnCommand(char id): GameCommand(id) {}

CheatTurnCommand::~CheatTurnCommand() {}

void CheatTurnCommand::execute(Game& game) { game.cheat_turn_time(); }
