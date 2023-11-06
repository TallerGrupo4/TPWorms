#include "./match.h"
#include <yaml-cpp/yaml.h>
#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "../common_src/constants.h"
#include "game_src/gameCommand.h"


Match::Match::Match(std::string map_route): game(map_route) , keep_running(true), match_started(false), queue(QUEUE_MAX_SIZE), id_counter(0) {
}



int Match::add_player() { //TODO: Make army (group of worms instead of one)
    int current_id = id_counter;
    game.add_player(current_id);  
    id_counter++;
    return id_counter;

}

void Match::start() {
    match_started = true;
    //broadcaster.broadcast(game.start_and_send());
    run();
}

void Match::run() {
    while (keep_running) {
            GameCommand* c;
            if (queue.try_pop(c)) {
                c->execute(game);
                delete c;
            }
            game.step();
            // broadcaster.broadcast(game.get_game_snapshot());
    }
}


Match::~Match() {}
