#include "client.h"

#include <iostream>

#include <sys/socket.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


Client::Client(const char* hostname, const char* servername):
        socket(hostname, servername),
        queue_sender_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_sender_match(std::make_shared<Queue<GameCommand>>(QUEUE_MAX_SIZE)),
        queue_receiver_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_receiver_match(std::make_shared<Queue<Snapshot>>(QUEUE_MAX_SIZE)),
        client_sender(std::make_unique<ClientSender>(socket, queue_sender_lobby, queue_sender_match,
                                                     in_match, is_dead)),
        client_receiver(std::make_unique<ClientReceiver>(socket, queue_receiver_lobby,
                                                         queue_receiver_match, in_match, is_dead)),
        parser() {
    // client_sender->start();
    // client_receiver->start();
    }

int Client::start() {
    try {
        client_sender->start();
        client_receiver->start();
        // THIS LAST COMMAND IS FOR THE BRIDGE BETWEEN QT AND SDL2
        // IT IS USED TO PUSHED THE "SUCCESFULLY JOIN/CREATED MATCH" MESSAGE (OR WHATEVER)
        bool last_command = true;
        // Here starts the client's main loop with QT (first while, like in a main menu)
        // and then SDL2 (when it is already in a match)
        Command command = INITIALIZE_COMMAND;
        GameCommand game_command;
        char code;
        while (client_sender->is_connected() && client_receiver->is_connected() && !is_dead) {
            get_action(command, game_command);
            if (!in_match || last_command) {
                code = command.code;
            } else {
                code = game_command.code;
            }
            switch (code) {
                case CASE_EXIT: {
                    is_dead = true;
                    stop();
                    break;
                }
                case CASE_INVALID: {
                    std::cout << "Invalid command" << std::endl;
                    break;
                }
                default:
                    if (in_match) {
                        if (last_command) {
                            queue_sender_lobby->close();
                        }
                        queue_sender_match->try_push(game_command);
                    } else {
                        queue_sender_lobby->try_push(command);
                    }
                    break;
            }
            if (is_dead)
                break;
            if (!in_match || last_command) {
                if (queue_receiver_lobby->try_pop(command))
                    print_command(command);
                if (in_match)
                    last_command = false;
            } else {
                Snapshot snapshot;
                if (queue_receiver_match->try_pop(snapshot))
                    print_snapshot(snapshot);
            }
        }
        // ----------

        if (!is_dead) {
            std::cout << "Client has finished because the server has closed the connection"
                      << std::endl;
            stop();
            return 1;
        }
        return 0;
    } catch (const LibError& e) {
        std::cout << "Client has finished because: " << e.what() << std::endl;
        return 1;
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the queue has been closed.
        std::cout << "Client has finished because: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Client has finished because of an unknown error" << std::endl;
        return 1;
    }
}

void Client::stop() {
    if (!in_match) {
        queue_sender_lobby->close();
    }
    queue_sender_match->close();
    queue_receiver_lobby->close();
    queue_receiver_match->close();
    socket.shutdown(SHUT_RDWR);
    client_sender->join();
    client_receiver->join();
}

void Client::get_action(Command& command, GameCommand& game_command) {
    if (in_match) {
        std::getline(std::cin, game_command.msg);
        parser.parse_sending_game_command(game_command);
    } else {
        std::getline(std::cin, command.msg);
        parser.parse_sending_command(command);
    }
}

void Client::print_snapshot(const Snapshot& snapshot) {
    std::cout << snapshot.msg << std::endl;
}

void Client::print_command(const Command& command) {
    switch (command.code) {
        // case CASE_CHAT: {
        //     std::cout << command.msg << std::endl;
        //     break;
        // }
        case CASE_JOIN: {
            std::cout << "There are " << +command.number_of_players
                      << " player/s in the match: " << +command.match_id << std::endl;
            break;
        }
        case CASE_CREATE: {
            std::cout << "Match succesfully created with the code: " << +command.match_id
                      << std::endl;
            break;
        }
        case CASE_MATCH_FULL: {
            std::cout << "The match " << +command.match_id
                      << " already has the maximum number of players."
                      << " Try again later or join another match." << std::endl;
            in_match = false;
            break;
        }
        case CASE_EXIT_SERVER: {
            std::cout << "The player " << +command.player_index
                      << " has left the match. "
                         "There are still "
                      << +command.number_of_players << " players in the match." << std::endl;
            break;
        }
        case CASE_MATCH_NOT_FOUND: {
            std::cout << "The match " << +command.match_id << " wan't found. "
                      << "Try another code or create a new one." << std::endl;
            in_match = false;
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            std::cout << "The match " << +command.match_id << " Already exists. "
                      << "Try with another code." << std::endl;
            in_match = false;
            break;
        }
        default:
            // Throw custom error, it should never reach this point!
            break;
    }
}

Command Client::pop_command() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    return queue_receiver_lobby->pop();
}

Snapshot Client::pop_snapshot() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    return queue_receiver_match->pop();
}

void Client::push_command(Command command) {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    queue_sender_lobby->push(command);
}

void Client::push_game_command(GameCommand game_command) {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    queue_sender_match->push(game_command);
}

void Client::exit() {
    is_dead = true;
    stop();
}


bool Client::is_connected() {
    return client_sender->is_connected() && client_receiver->is_connected() && !is_dead;
}

Client::~Client() {}
