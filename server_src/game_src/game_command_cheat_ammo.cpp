#include "game_command_cheat_ammo.h"

CheatAmmoCommand::CheatAmmoCommand(char id): GameCommand(id) {}

CheatAmmoCommand::~CheatAmmoCommand() {}

void CheatAmmoCommand::execute(Game& game) { game.cheat_ammo(id_worm); }
