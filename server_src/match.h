#include <string>
#include "game_src/game.h"

class GameCommand;

#ifndef MATCH_H
#define MATCH_H




class Match: public Thread {
    private:
        Game game;
        std::string name;
        bool keep_running;
        bool match_started;
        Queue<GameCommand*> queue;
        // Broadcaster& broadcaster;
        int id_counter;

        
    public:
        Match(std::string map_route);
        ~Match();
        int add_player();
        void stop();
        void run() override;
        void start();
        void send_map();
        
        void move_player(int direction, int id);
        void push_command(GameCommand* command);
}; 

#endif