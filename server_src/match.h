#include <box2d/box2d.h>
#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include <vector>
#include <string>
#include "gamebuilder.h"

class GameCommand;

#ifndef MATCH_H
#define MATCH_H


class Match: public Thread {
    private:
        std::string name;
        b2World world;
        GameBuilder builder;
        bool keep_running;
        bool match_started;
        std::vector<b2Body*> players;
        Queue<GameCommand*> queue;
        // Broadcaster& broadcaster;
        int turn;
        int id_counter;

        
    public:
        Match(std::string map_route);
        ~Match();
        int add_player();
        void stop();
        void run() override;
        void start();
        void move_player(int direction, int id);
        void push_command(GameCommand* command);
}; 

#endif