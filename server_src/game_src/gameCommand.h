#include <box2d/box2d.h>

#include "../../common_src/constants.h"

#include "game.h"


// #define DER 1
// #define IZQ -1

// MOVE THIS TO COMMON_SRC

class __GameCommand {
protected:
    char code = -1;
    std::string msg = "";
    uint8_t number_of_players = 0;
    uint match_id = 0;
    int id;

public:
    __GameCommand();
    __GameCommand(int id): id(id){};
    ~__GameCommand();
    void virtual execute(Game& game);
    static __GameCommand* createCommand(int id, int direction, int type);
};

class __MovCommand: public __GameCommand {
    int direction;

public:
    __MovCommand(int id, int direction): __GameCommand(id), direction(direction) {}
    ~__MovCommand() {}
    void execute(Game& game) override { game.move_player(direction, id); }
};

__GameCommand* __GameCommand::createCommand(int id, int direction, int type) {
    switch (type) {
        case MOV:
            return new __MovCommand(id, direction);
    }
    return nullptr;
}

