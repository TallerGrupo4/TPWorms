#include <memory>
#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


class GameCommand {

protected:
    uint8_t id_worm = -1;
    int direction = 0;


public:

    GameCommand(uint8_t id = -1, int direction = 0): id_worm(id), direction(direction) {};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
    static std::shared_ptr<GameCommand> createCommand(uint8_t id, int direction, int type);
};


class MoveCommand: public GameCommand {
public:
    MoveCommand(uint8_t id, int direction): GameCommand(id, direction) {}
    ~MoveCommand() {}
    void execute(Game& game) override { game.move_player(id_worm, direction); }
};



class ExitCommand: public GameCommand {
public:
    ExitCommand(uint8_t id) : GameCommand(id) {}
    ~ExitCommand() {}
    void execute(Game& game) override { game.remove_player(id_worm); }
};





inline std::shared_ptr<GameCommand> GameCommand::createCommand(uint8_t id, int direction, int type) {
    switch (type) {
        case MOV:
            return std::make_shared<MoveCommand>(id, direction);
            break;
        case CASE_EXIT_SERVER:
            return std::make_shared<ExitCommand>(id);
            break;
    }
    return nullptr;
}


#endif  // GAME_COMMAND_H
