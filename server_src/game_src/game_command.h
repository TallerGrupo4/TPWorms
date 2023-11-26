#include <memory>
#include "game.h"
#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

struct MoveCommandAttributes {
    int direction;
};

struct ShootCommandAttributes {
    char id;
    float angle;
    int potency;
    int weapon_type;
};

class GameCommand {
protected:
    // Make this private and add a getter
    char id_worm = -1; 
    int direction;

public:
    GameCommand(char id = -1, int direction = 0): id_worm(id), direction(direction) {};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
    static std::shared_ptr<GameCommand> createCommand(int id, MoveCommandAttributes move , ShootCommandAttributes shoot , int type);
};


class MoveCommand: public GameCommand {
public:
    int get_direction() { return direction; }
    MoveCommand(char id, int direction): GameCommand(id, direction) {}
    ~MoveCommand() {}
    void execute(Game& game) override { 
        game.move_player(id_worm, direction); }
};

class JumpCommand: public GameCommand {
    public:
    int get_direction() { return direction; }
    JumpCommand(char id, int direction): GameCommand(id, direction) {}
    ~JumpCommand() {}
    void execute(Game& game) override { game.jump_player(id_worm, direction); }

};

class ExitCommand: public GameCommand {
    char army_id;
public:
    ExitCommand(char army_id) : GameCommand(), army_id(army_id) {}
    ~ExitCommand() {}
    void execute(Game& game) override { game.remove_player(army_id); }
};




inline std::shared_ptr<GameCommand> GameCommand::createCommand(int id, MoveCommandAttributes move , ShootCommandAttributes shoot , int type) {
    switch (type) {
        case MOV:
            return std::make_shared<MoveCommand>(id, move.direction);
            break;
        // case SHOOT:
        //     return std::make_shared<ShootCommand>(id, shoot.angle, shoot.potency, shoot.weapon_type);
        //     break;
        case JUMP:
            return std::make_shared<JumpCommand>(id, move.direction);
            break;
        case CASE_EXIT_SERVER:
            return std::make_shared<ExitCommand>(id);
            break;
    }
    return nullptr;
}


#endif  // GAME_COMMAND_H