#include <box2d/box2d.h>
#include "game.h"
#include "../../common_src/constants.h"


// #define DER 1 
// #define IZQ -1


class GameCommand{
protected:
    int id;
public:
    GameCommand(int id): id(id){};
    ~GameCommand();
    void virtual execute(Game& game) ;
    static GameCommand* createCommand(int id , int direction, int type);
};

class MovCommand : public GameCommand{
    int direction;
    public: 
    MovCommand(int id, int direction): GameCommand(id), direction(direction) {}
    ~MovCommand(){}
    void execute(Game& game) override {
        game.move_player(direction, id);
    }

};

GameCommand* GameCommand::createCommand(int id , int direction, int type){
        switch (type){
            case MOV:
                return new MovCommand(id ,direction);
        }
        return nullptr;
}   