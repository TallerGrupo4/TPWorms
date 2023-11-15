#include "./match.h"
#include <cstdint>
#include <iostream>
#include <memory>

#include <yaml-cpp/yaml.h>

#include "../common_src/constants.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"


Match::Match(std::string map_route):
        game(map_route),
        keep_running(true),
        match_started(false),
        // queue(std::make_shared<Queue<GameCommand*>>(QUEUE_MAX_SIZE)),
        queue(std::make_shared<Queue<std::shared_ptr<GameCommand>>>(QUEUE_MAX_SIZE)),
        id_counter(0), start_loop_time(std::chrono::high_resolution_clock::now()), 
        total_loop_time(0) {}


uint8_t Match::add_player(std::shared_ptr<Queue<Snapshot>>
                              player_queue) {  // TODO: Make army (group of worms instead of one)
    // if (match_started) throw MatchAlreadyStarted();
    if (id_counter >= MAX_PLAYERS)
        throw MatchFull();
    uint8_t current_id = id_counter;
    players_queues.push_back(player_queue);
    id_counter++;
    return current_id;
}

void Match::start_match() {
    // send_map();
    for (int i = 0; i < id_counter; i++) {
        game.add_player(id_counter);
    }
    match_started = true;
    this->start();
}

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

void Match::send_map() {
    Snapshot map = game.start_and_send();
    push_all_players(map);
}

void Match::run() {
    // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
    /*
    int rate = FRAME_TIME;
    std::shared_ptr<GameCommand> game_command;
    auto time_1 = std::chrono::high_resolution_clock::now();
    int it = 0;
    */
    // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
    try {
        while (keep_running) {
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
            /*
            while (true) {
                commands = getAllCommands();
                for command in commands {
                    command->execute(gamewordl);
                }
                loopsToSimulate = calculateRate(); // depende de si te atrasaste o no
                gamewordl.simulateStep(loopsToSimulate);
                broadcastSnapshot();  
                sleep(...);
            }
            */
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
            std::cout << "Match running" << std::endl;
             
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
            /*
            while (queue->try_pop(game_command)) {
                std::cout << "GameCommand received" << std::endl;
                // The game_command should notify the game if it is a end_turn game_command
                game_command->execute(game)
            }
            // Create class Timer that will count from 0 to MAX_TIME (ticks)
            game->step(it_diff);  // Check if turn ended (sum ticks, etc)
            
            // All of the above is what the game.get_game_snapshot() should do (and more)
            Snapshot snapshot = game.get_game_snapshot();
            // Push to all players
            push_all_players(snapshot);
            */
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!

            // If worms is empty, it will send the whole map
            // Else, it will send only the worms
            // Doing it this way, saves us from doing polymorfism in the Snapshot class.
            // std::vector<WormSnapshot> worms;
            // PlatformSnapshot platform('p', 0, 0, 0);
            // std::vector<PlatformSnapshot> platforms;
            // platforms.push_back(platform);
            // Snapshot snapshot(worms, platforms);

            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
            /*
            // Now it comes the part where we calculate the time we spent in the loop
            auto time_2 = std::chrono::high_resolution_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_2 - time_1);//count casts to int
            int rest = rate - diff.count();
            // Rest if it is positive, else don't rest
            if (rest > 0) std::this_thread::sleep_for(std::chrono::milliseconds(rest));
            */
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!

            // THIS IS NOT MATEO BUT IT IS IMPORTANT!!!!!!!!!!
            // If the game has ended, we should stop the match
            // if (game.has_ended()) {
            //     stop();
            // }

            // Push to all players
            // push_all_players(snapshot);


            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
            /*
            // Now we reset the time_1 (our 'clock')
            time_1 = std::chrono::high_resolution_clock::now();

            // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            auto it_acum = it;
            it = it + 1;
            */
            // !!!!!!!!!!!!!!!MATEO!!!!!!!!!!!!!!!!!
        }
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
