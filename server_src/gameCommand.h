#include <box2d/box2d.h>

#include "../common_src/constants.h"

#include "match.h"


// #define DER 1
// #define IZQ -1


class GameCommand {
protected:
    int id;
    Match& match;

public:
    GameCommand(int id, Match& match): id(id), match(match){};
    ~GameCommand();
    void virtual execute();
    static GameCommand* createCommand(Match& match, int id, int direction, int type);
};

class MovCommand: public GameCommand {
    int direction;

public:
    MovCommand(Match& match, int id, int direction): GameCommand(id, match), direction(direction) {}
    ~MovCommand() {}
    void execute() override { match.move_player(direction, id); }
};

GameCommand* GameCommand::createCommand(Match& match, int id, int direction, int type) {
    switch (type) {
        case MOV:
            return new MovCommand(match, id, direction);
    }
    return nullptr;
}