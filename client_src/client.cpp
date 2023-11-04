#include "client.h"

#include <iostream>

#include <sys/socket.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


Client::Client(const char* hostname, const char* servername):
        socket(hostname, servername),
        queue_sender(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_receiver(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        client_sender(std::make_unique<ClientSender>(socket, queue_sender, in_match)),
        client_receiver(std::make_unique<ClientReceiver>(socket, queue_receiver, in_match)),
        parser() {}

int Client::start() {
    try {
        client_sender->start();
        client_receiver->start();

        // Here starts the client's main loop with QT (first while, like in a main menu)
        // and then SDL2 (when it is already in a match)
        Command command = INITIALIZE_COMMAND;
        while (client_sender->is_connected() && client_receiver->is_connected() && !is_dead) {
            get_command(command);
            if (!in_match && command.code != CASE_JOIN && command.code != CASE_CREATE &&
                command.code != CASE_EXIT) {
                command.code = CASE_INVALID;
            }
            switch (command.code) {
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
                    queue_sender->try_push(command);
                    break;
            }
            if (queue_receiver->try_pop(command))
                print_command(command);
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
    } catch (...) {
        std::cerr << "Client has finished because of an unknown error" << std::endl;
        return 1;
    }
}

void Client::stop() {
    socket.shutdown(SHUT_RDWR);
    queue_sender->close();
    queue_receiver->close();
    client_sender->join();
    client_receiver->join();
}

void Client::get_command(Command& command) {
    std::getline(std::cin, command.msg);
    parser.parse_sending_command(command);
}

void Client::print_command(const Command& command) {
    switch (command.code) {
        case CASE_CHAT: {
            std::cout << command.msg << std::endl;
            break;
        }
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

Client::~Client() {}
