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
public:
    // Make this private and add a getter
    char id_worm = -1; 
    bool is_start = false;

    GameCommand(char id = -1, bool _is_start = false): id_worm(id), is_start(_is_start) {};
    ~GameCommand() = default;


    void virtual execute(Game& game) { return; };
    static std::shared_ptr<GameCommand> createCommand(int id, MoveCommandAttributes move , ShootCommandAttributes shoot , int type);
};


// This could be a Command from the lobby
class StartCommand: public GameCommand {
public:
    StartCommand(): GameCommand(-1 , true) {}
    ~StartCommand() {}
};



class MoveCommand: public GameCommand {
private:
    int direction;

public:
    MoveCommand(char id, int direction): GameCommand(id), direction(direction) {}
    ~MoveCommand() {}
    void execute(Game& game) override { game.move_player(id_worm, direction); }
};

class JumpCommand: public GameCommand {
    private:
    int direction;

    public:
    JumpCommand(char id, int direction): GameCommand(id), direction(direction) {}
    ~JumpCommand() {}
    void execute(Game& game) override { game.jump_player(id_worm, direction); }

};

class ExitCommand: public GameCommand {
public:
    ExitCommand(char id) : GameCommand(id) {}
    ~ExitCommand() {}
    void execute(Game& game) override { game.remove_player(id_worm); }
};


// class ShootCommand: public GameCommand {
//     private:
//     float angle;
//     int potency;
//     std::shared_ptr<Weapon> weapon;

//     public:
//     ShootCommand(char id , float angle , int potency, int weapon_type) : GameCommand(id) , angle(angle) , potency(potency)  {
//         weapon = std::shared_ptr<Weapon> (Weapon::Create_Weapon(weapon_type));
//     }
//     ~ShootCommand() {}

//     void execute(Game& game) override { game.shoot_player(id_worm , angle , potency , weapon); }

// };


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