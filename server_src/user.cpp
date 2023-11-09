#include "user.h"

#include <memory>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"

#include "match.h"

User::User(Socket&& skt, MonitorMatches& _monitor_matches):
        socket(std::move(skt)),
        parser(),
        protocol(socket, parser),
        sender(std::make_unique<UserSender>(socket, protocol)),
        monitor_matches(_monitor_matches) {}

void User::run() {
    try {
        handle_lobby();
        sender->start();
        handle_match();
    } catch (const LibError& err) {
        _is_dead = true;
        if (queue_match) {
            try {
                std::shared_ptr<ExitCommand> exit_command;
                queue_match->push(exit_command);
                sender->stop();
                sender->join();
            } catch (const PlayerNotFound& e) {
                // It is an expected error but it should never reach this point
            } catch (const ClosedQueue& e) {
                // It is an expected error but it should never reach this point
            }
        }
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in the User"
                  << std::endl;
    }
}


void User::handle_match() {
    while (protocol.is_connected()) {
        std::shared_ptr<GameCommand> game_command = protocol.recv_game_command();
        if (game_command->is_start) {
            try {
                monitor_matches.start_match(match_id);
                std::cout << "Match started with id: " << match_id << std::endl;
                continue;
            } catch (const MatchNotFound& err) {
                std::cout << "Match not found with id: " << match_id << std::endl;
                continue;
            } catch (const MatchAlreadyStarted& err) {
                std::cout << "Match already started with id: " << match_id << std::endl;
                continue;
            }
        }
        queue_match->push(game_command);
    }
}

void User::handle_lobby() {
    while (protocol.is_connected()) {
        Command command = INITIALIZE_COMMAND;
        if (protocol.recv_command(command) == SOCKET_FAILED) {
            throw LibError(errno, "Socket failed");
        }
        if (interpretate_command_in_lobby(command)) {
            break;
        }
    }
}

bool User::interpretate_command_in_lobby(Command& command) {
    bool in_match = false;
    switch (command.code) {
        case CASE_CREATE: {
            try {
                queue_match = monitor_matches.create_match(sender->get_queue(),
                command.match_id);
                in_match = true;
                match_id = command.match_id;
                std::cout << "Match created with id: " << match_id << std::endl;
            } catch (const MatchAlreadyExists& err) {
                command.code = CASE_MATCH_ALREADY_EXISTS;
                std::cout << "Match already exists with id: " << command.match_id << std::endl;
            }
            // parser.parse_sending_command(command);
            protocol.send_command(command);
            break;
        }
        case CASE_JOIN: {
            try {
                queue_match = monitor_matches.join_match(sender->get_queue(), command.match_id);
                in_match = true;
                std::cout << "Match joined with id: " << command.match_id << std::endl;
            } catch (const MatchFull& err) {
                command.code = CASE_MATCH_FULL;
                std::cout << "Match is full with id: " << command.match_id << std::endl;
            } catch (const MatchNotFound& err) {
                command.code = CASE_MATCH_NOT_FOUND;
                std::cout << "Match not found with id: " << command.match_id << std::endl;
            }
            // parser.parse_sending_command(command);
            protocol.send_command(command);
            break;
        }
        default:
            break;
    }
    return in_match;
}


void User::stop() {
    try {
        if (protocol.is_connected())
            socket.shutdown(SHUT_RDWR);
        sender->stop();
        sender->join();
    } catch (const LibError& err) {
        std::cout << "Something went wrong and an exception was caught in the User"
                  << " while stoping it: " << err.what() << std::endl;
    } catch (...) {
        std::cerr << R"(Something went wrong and \
            an unknown exception was caught in the User while stoping it: )"
                  << std::endl;
    }
}

bool User::is_dead() {
    return _is_dead;

}

User::~User() {}
