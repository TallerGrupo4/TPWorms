#include "client.h"

#include <iostream>

#include <sys/socket.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


Client::Client(const char* hostname, const char* servername):
        socket(hostname, servername),
        queue_sender_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_sender_match(std::make_shared<Queue<Action>>(QUEUE_MAX_SIZE)),
        queue_receiver_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_receiver_match(std::make_shared<Queue<Snapshot>>(QUEUE_MAX_SIZE)),
        client_sender(std::make_unique<ClientSender>(socket, queue_sender_lobby, queue_sender_match,
                                                     in_match, is_dead)),
        client_receiver(std::make_unique<ClientReceiver>(socket, queue_receiver_lobby,
                                                         queue_receiver_match, in_match, is_dead)),
        parser(), protocol(socket, parser) {
    }

void Client::start() {
    client_sender->start();
    client_receiver->start();
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

void Client::get_action(Command& command, Action& action) {
    if (in_match) {
        std::cout << "Wating for action: " << std::endl;
        std::getline(std::cin, action.msg);
        parser.parse_sending_action(action);
    } else {
        std::cout << "Wating for a lobby command: " << std::endl;
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

Command Client::recv_lobby_command() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    Command command = INITIALIZE_COMMAND;
    protocol.recv_command(command);
    return command;
}

Snapshot Client::recv_snapshot() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    Snapshot snapshot;
    snapshot.code = DEFAULT;
    if (queue_receiver_match->try_pop(snapshot)) snapshot.code = CASE_CHAT;
    return snapshot;
}

void Client::send_lobby_command(Command command) {
    if (!protocol.is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    // queue_sender_lobby->push(command);
    protocol.send_command(command);
}

void Client::send_action(Action action) {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    queue_sender_match->try_push(action);
}

void Client::exit() {
    is_dead = true;
    stop();
}


bool Client::is_connected() {
    return client_sender->is_connected() && client_receiver->is_connected() && !is_dead;
}

Client::~Client() {}
