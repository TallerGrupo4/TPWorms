#include "./match.h"

#include <yaml-cpp/yaml.h>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "game_src/gameCommand.h"


Match::Match::Match(std::string map_route):
        game(map_route),
        keep_running(true),
        match_started(false),
        queue(std::make_shared<Queue<GameCommand*>>(QUEUE_MAX_SIZE)),
        id_counter(0) {}


int Match::add_player(std::shared_ptr<Queue<Snapshot>>
                              player_queue) {  // TODO: Make army (group of worms instead of one)
    // if (match_started) throw MatchAlreadyStarted();
    if (id_counter >= MAX_PLAYERS)
        throw MatchFull();
    int current_id = id_counter;
    players_queues.push_back(player_queue);
    id_counter++;
    return current_id;
}

void Match::start() {
    send_map();
    for (int i = 0; i < id_counter; i++) {
        game.add_player(id_counter);
    }
    match_started = true;
    run();
}

void Match::push_all_players(Snapshot snapshot) {
    for (auto& player_queue: players_queues) {
        player_queue->push(snapshot);
    }
}

void Match::send_map() {
    MapSnapshot map = game.start_and_send();
    push_all_players(map);
}

void Match::run() {
    while (keep_running) {
        GameCommand* c;
        if (queue->try_pop(c)) {
            c->execute(game);
            delete c;
        }
        game.step();
        GameSnapshot snapshot = game.get_game_snapshot();
        push_all_players(snapshot);
    }
}


std::shared_ptr<Queue<GameCommand*>> Match::get_queue() { return queue; }

Match::~Match() {}
