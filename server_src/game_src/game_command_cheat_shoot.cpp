#include "game_command_cheat_shoot.h"

CheatShootCommand::CheatShootCommand(char id): GameCommand(id) {}

CheatShootCommand::~CheatShootCommand() {}

void CheatShootCommand::execute(Game& game){
    game.toggle_shoot_cheat(id_worm);
}