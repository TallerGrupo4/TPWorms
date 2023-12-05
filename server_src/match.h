#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <box2d/box2d.h>

#include "../common_src/clock.h"
#include "../common_src/custom_errors.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "game_src/game.h"
#include "game_src/game_command.h"

#include "map.h"


#ifndef MATCH_H
#define MATCH_H


class Match: public Thread {
private:
    Map map;
    Game game;
    std::string name;
    bool keep_running;
    bool match_started;
    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> queue;
    std::vector<std::shared_ptr<Queue<Snapshot>>> players_queues;
    char id_counter;

    void send_initial_data();
    void push_all_players(const Snapshot& snapshot);


public:
    Match();
    ~Match();

    uint8_t add_player(std::shared_ptr<Queue<Snapshot>> player_queue);

    void stop();

    bool has_started();

    std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> get_queue();

    uint8_t get_number_of_players();

    void run() override;
    void execute_and_step(int iter);
    void start_game(const Map& map);

    bool has_ended();

    std::string get_map_name();
};

#endif
