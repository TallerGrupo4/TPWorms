#include <memory>
#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


class GameCommand {
public:
    int id_worm = -1;

    GameCommand(int id): id_worm(id){};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
    static std::unique_ptr<GameCommand> createCommand(int id, int direction, int type);
};

class MoveCommand: public GameCommand {
    int direction;

public:
    MoveCommand(int id, int direction): GameCommand(id), direction(direction) {}
    ~MoveCommand() {}
    void execute(Game& game) override { game.move_player(id_worm, direction); }
};

std::unique_ptr<GameCommand> GameCommand::createCommand(int id, int direction, int type) {
    switch (type) {
        case MOV:
            return std::make_unique<MoveCommand>(id, direction);
    }
    return nullptr;
}


#endif  // GAME_COMMAND_H
