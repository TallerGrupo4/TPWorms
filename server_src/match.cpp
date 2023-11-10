#include "./match.h"
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
    while (keep_running) {
        std::shared_ptr<GameCommand> game_command;
        try {
            if (queue->try_pop(game_command)) {
                std::cout << "GameCommand received" << std::endl;
                // game_command->execute(game);
            }
        } catch (const ClosedQueue& err) {
            std::cout << "Queue closed" << std::endl;
            break;
        }
        // game.step();
        // GameSnapshot snapshot = game.get_game_snapshot();
        // Snapshot snapshot;
        // snapshot.code = 1;
        // snapshot.msg = "Hello! There are " + std::to_string(id_counter) + " players in this match";
        // game.step();
        // Snapshot snapshot = game.get_game_snapshot();

        // It doesn't matter what I am sending.
        // It is just to prove that the server and client are working with snapshots (and they do).
        std::vector<WormSnapshot> worms;
        PlatformSnapshot platform('p', 0, 0, 0);
        std::vector<PlatformSnapshot> platforms;
        platforms.push_back(platform);
        Snapshot snapshot(worms, platforms);
        push_all_players(snapshot);

        // std::this_thread::sleep_for(std::chrono::milliseconds(16));

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}


void Match::stop() {
    keep_running = false;
}

bool Match::has_started() { return match_started; }

// std::shared_ptr<Queue<GameCommand*>> Match::get_queue() { return queue; }
std::shared_ptr<Queue<std::shared_ptr<GameCommand>>> Match::get_queue() { return queue; }

Match::~Match() {}
