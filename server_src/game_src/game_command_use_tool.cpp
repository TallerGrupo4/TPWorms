#include "game_command_use_tool.h"

UseToolCommand::UseToolCommand(int id, int potency, float pos_x, float pos_y): GameCommand(id), potency(potency), pos_x(pos_x), pos_y(pos_y) {}

UseToolCommand::~UseToolCommand() {}

void UseToolCommand::execute(Game& game) {
    game.player_use_tool(id_worm, potency , pos_x , pos_y );
}

int UseToolCommand::get_potency() {
    return potency;
}

float UseToolCommand::get_pos_x() {
    return pos_x;
}

float UseToolCommand::get_pos_y() {
    return pos_y;
}
