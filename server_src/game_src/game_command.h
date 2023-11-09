#include <memory>
#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


class GameCommand {
public:
    // Make this private and add a getter
    char id_worm = -1;
    bool is_start = false;

    GameCommand(char id = -1, bool _is_start = false): id_worm(id), is_start(_is_start) {};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
    // static std::shared_ptr<GameCommand> createCommand(char id, int direction, int type);
};


class MoveCommand: public GameCommand {
private:
    int direction;

public:
    MoveCommand(char id, int direction): GameCommand(id), direction(direction) {}
    ~MoveCommand() {}
    void execute(Game& game) override { game.move_player(id_worm, direction); }
};



class ExitCommand: public GameCommand {
public:
    ExitCommand(char id) : GameCommand(id) {}
    ~ExitCommand() {}
    // void execute(Game& game) override { game.remove_player(id_worm); }
};



class StartCommand: public GameCommand {
public:
    StartCommand(): GameCommand(-1 , true) {}
    ~StartCommand() {}
    void execute(Game& game) override { game.start_and_send(); }
};



// std::shared_ptr<GameCommand> GameCommand::createCommand(char id, int direction, int type) {
//     switch (type) {
//         case MOV:
//             return std::make_shared<MoveCommand>(id, direction);
//             break;
//         case CASE_EXIT_SERVER:
//             return std::make_shared<ExitCommand>(id);
//             break;
//     }
//     return nullptr;
// }


#endif  // GAME_COMMAND_H
