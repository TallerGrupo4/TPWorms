#include "game_command_cheat_life.h"

CheatLifeCommand::CheatLifeCommand(char id): GameCommand(id) {}

CheatLifeCommand::~CheatLifeCommand() {}

void CheatLifeCommand::execute(Game& game){
    game.cheat_life(id_worm);
}