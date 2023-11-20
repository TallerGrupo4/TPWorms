#include "./match.h"
#include <cstdint>
#include <iostream>
#include <memory>

#include <yaml-cpp/yaml.h>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"


Match::Match():
        map(),
        game(),
        keep_running(true),
        match_started(false),
        queue(std::make_shared<Queue<std::shared_ptr<GameCommand>>>(QUEUE_MAX_SIZE)),
        id_counter(0) {}


uint8_t Match::add_player(std::shared_ptr<Queue<Snapshot>>
                              player_queue) {  // TODO: Make army (group of worms instead of one)
    if (match_started) throw MatchAlreadyStarted();
    if (id_counter >= MAX_PLAYERS)
        throw MatchFull();
    uint8_t current_id = id_counter;
    players_queues.push_back(player_queue);
    id_counter++;
    return current_id;
}

void Match::start_game(Map& map) {
    this->map = map;
    send_initial_data();
    match_started = true;
    this->start();
}

uint8_t Match::get_number_of_players() { return id_counter; }

void Match::push_all_players(Snapshot snapshot) {
    for (auto& player_queue: players_queues) {
        try {
            player_queue->push(snapshot);
        } catch (const ClosedQueue& err) {
            /*
            * It is an expected error, this should occur
            * when stopping the whole server or when a 
            * client has disconnected, I think...
            * If the client has disconnected, we should
            * remove it from the match, unless we do that
            * in other place, but I believe that here could
            * be a good place to do it.
            */
            // players_queues.erase(std::remove(players_queues.begin(), players_queues.end(), player_queue), players_queues.end());
            continue;
        } 
    }
}

void Match::send_initial_data() {
    Snapshot start_snap = game.start_and_send(map , id_counter);
    push_all_players(start_snap);
}

void Match::run(){
    Clock clock([this](int iter) { execute_and_step(iter); }, FRAME_TIME, keep_running);
    clock.tick();
}

void Match::execute_and_step(int iter) {
    try {
        std::shared_ptr<GameCommand> game_command;
        while (queue->try_pop(game_command)) {
            // The game_command should notify the game if it is a end_turn game_command
            game_command->execute(game);
        }
        // Iter is the number of times you should advance frames, not the time
        game.step(iter);// Check if turn ended (sum ticks, etc)
        
        Snapshot snapshot = game.get_game_snapshot();
        push_all_players(snapshot);

        // If the game has ended, we should stop the match
        // if (game.has_ended()) {
        //     stop();
        // }
    } catch (const ClosedQueue& err) {
          if (!keep_running) return;
            std::cerr << "Error: " << err.what() << std::endl;
            keep_running = false;
    }
}


void Match::stop() {
    keep_running = false;
}

bool Match::has_started() { return match_started; }

// std::shared_ptr<Queue<GameCommand*>> Match::get_queue() { return queue; }
std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> Match::get_queue() { return queue; }

std::string Match::get_map_name() { return name; }

Match::~Match() {
    // Perhaps it would be better to close the queue here
    // queue->close();
}
