#include <iostream>

#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

class GameCommand {
public:
    char code = -1;
    std::string msg = "";
    uint8_t number_of_players = 0;
    uint match_id = 0;


    int id_worm = -1;
    int movement_x = 0;

    GameCommand() = default;
    // GameCommand(int id): id(id){};
    ~GameCommand() = default;
    // void virtual execute(Game& game) {
    //     std::cout << "GameCommand::execute()" << std::endl;
    // }
    // void virtual execute(Game& game);
    // static GameCommand* createCommand(int id, int direction, int type);
};

// class MovCommand: public GameCommand {
//     int direction;

// public:
//     MovCommand(int id, int direction): GameCommand(id), direction(direction) {}
//     ~MovCommand() {}
//     // void execute(Game& game) override { game.move_player(direction, id); }
// };

// GameCommand* GameCommand::createCommand(int id, int direction, int type) {
//     switch (type) {
//         case MOV:
//             return new MovCommand(id, direction);
//     }
//     return nullptr;
// }

#endif  // GAME_COMMAND_H