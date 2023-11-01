#include "server_client.h"

#include <utility>

#include <sys/socket.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"

ServerClient::ServerClient(Socket&& skt, MonitorMatches& _monitor_matches):
        socket(std::move(skt)),
        queue(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        parser(),
        protocol(socket, parser),
        sender(std::make_unique<ServerClientSender>(socket, queue, protocol)),
        monitor_matches(_monitor_matches) {}

void ServerClient::run() {
    try {
        sender->start();

        while (protocol.is_connected()) {
            Command command = INITIALIZE_COMMAND;
            if (protocol.recv(command) == SOCKET_FAILED) {
                // We have to actually catch a custom error here called SOCKET_FAILED
                throw LibError(errno, "Socket failed");
            }
            interpretate_command(command);
        }
    } catch (const LibError& err) {
        // if (!protocol.is_connected()) {
        _is_dead = true;
        Command command = INITIALIZE_COMMAND;
        command.code = CASE_EXIT_SERVER;
        if (monitor_match) {
            try {
                command.player_index = monitor_match->get_player_index(queue);
                monitor_match->remove(queue);
                command.number_of_players = monitor_match->get_players();
            } catch (const PlayerNotFound& e) {
                // It is an expected error but it should never reach this point
            }
            monitor_match->push(command);
        }
        // } else {
        // We must do something about the client eitherway if we catch an error
        // std::cout << "An error was caught in the ServerClient: " << err.what() << std::endl;
        // }
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in the ServerClient"
                  << std::endl;
    }
}

void ServerClient::stop() {
    try {
        if (protocol.is_connected())
            socket.shutdown(SHUT_RDWR);
        queue->close();
        sender->join();
    } catch (const LibError& err) {
        std::cout << "Something went wrong and an exception was caught in the ServerClient"
                  << " while stoping it: " << err.what() << std::endl;
    } catch (...) {
        std::cerr << R"(Something went wrong and \
            an unknown exception was caught in the ServerClient while stoping it: )"
                  << std::endl;
    }
}

bool ServerClient::is_dead() {
    try {
        if (_is_dead) {
            queue->close();
            if (monitor_match)
                monitor_match->remove(queue);
            sender->join();
        }
        return _is_dead;
    } catch (const LibError& err) {
        std::cout << "Something went wrong and an unknown exception was caught in the ServerClient"
                  << " while checking if it is dead: " << err.what() << std::endl;
        return _is_dead;
    } catch (const ClosedQueue& err) {
        std::cout << "Something went wrong and an unknown exception was caught in the ServerClient"
                  << " while checking if it is dead: " << err.what() << std::endl;
        return _is_dead;
    } catch (...) {
        std::cerr << R"(Something went wrong and \
            an unknown exception was caught in the ServerClient while checking if it is dead: )"
                  << std::endl;
        return _is_dead;
    }
}

void ServerClient::interpretate_command(Command& command) {
    switch (command.code) {
        case CASE_CREATE: {
            try {
                monitor_match = monitor_matches.create(queue, command.match_id);
            } catch (const MatchAlreadyExists& err) {
                command.code = CASE_MATCH_ALREADY_EXISTS;
                queue->push(command);
                break;
            }
            monitor_match->push(command);
            break;
        }
        case CASE_JOIN: {
            try {
                monitor_match = monitor_matches.join(queue, command.match_id);
            } catch (const MatchFull& err) {
                command.code = CASE_MATCH_FULL;
                queue->push(command);
                break;
            } catch (const MatchNotFound& err) {
                command.code = CASE_MATCH_NOT_FOUND;
                queue->push(command);
                break;
            }
            command.number_of_players = monitor_match->get_players();
            monitor_match->push(command);
            break;
        }
        case CASE_CHAT: {
            monitor_match->push(command);
            break;
        }
        default:
            break;
    }
}

ServerClient::~ServerClient() {}
