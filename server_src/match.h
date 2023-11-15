#include <string>
#include <vector>
#include <chrono>

#include <box2d/box2d.h>

#include "../common_src/custom_errors.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "game_src/game_command.h"
#include "game_src/game.h"
#include "map.h"
#include "../common_src/clock.h"



#ifndef MATCH_H
#define MATCH_H


class Match: public Thread {
    private:
        Map map;
        Game game;
        std::string name;
        bool keep_running;
        bool match_started;
        // This doesn't need to be a shared_ptr, we could pass a reference of it to the receiver
        std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> queue;
        std::vector<std::shared_ptr<Queue<Snapshot>>> players_queues;
        char id_counter;
        std::chrono::high_resolution_clock::time_point start_loop_time;
        uint32_t total_loop_time; 
        
        void send_map();
        void move_player(int direction, char id);
        void push_all_players(Snapshot snapshot);


    public:
        Match(Map& map);
        ~Match();

        uint8_t add_player(std::shared_ptr<Queue<Snapshot>> player_queue);

        void stop();

        bool has_started();
        
        // std::shared_ptr<Queue<GameCommand*>> get_queue();
        std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> get_queue();
        
        void run() override;
        void execute_and_step(int iter);
        void start_game();

        std::string get_map_name();
};

#endif