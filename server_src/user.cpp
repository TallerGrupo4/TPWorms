#include "user.h"

#include <memory>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/command.h"
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
        if (is_creator) handle_starting_match();
        sender->start();
        handle_match();
    } catch (const LibError& err) {
        std::cout << "User connection was closed: "
                  << err.what() << std::endl;
        _is_dead = true;
        if (queue_match) {
            try {
                std::shared_ptr<ExitCommand> exit_command = std::make_shared<ExitCommand>(my_army_id);
                queue_match->push(exit_command);
                sender->stop();
                sender->join();
            } catch (const PlayerNotFound& e) {
                // It is an 'expected' error but it should never reach this point
            } catch (const ClosedQueue& e) {
                // It is an 'expected' error but it should never reach this point
            }
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught in the User: "
                  << err.what() << std::endl;
    }catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in the User"
                  << std::endl;
    }
}

void User::handle_starting_match() {
    while (protocol.is_connected()) {
        Command command = protocol.recv_command();
        if (command.get_code() == CASE_START) {
            try {
                if (match_id != command.get_match_id()) {
                    // It should never reach this point I think
                    std::cout << "Match id does not match with the one in the server" << std::endl;
                    // TODO: KILL THIS CORRUPTED CLIENT
                    continue;
                }
                monitor_matches.start_match(match_id, command.get_map_name());
                std::cout << "Match started with id: " << match_id << std::endl;
                return;
            } catch (const MatchNotFound& err) {
                // It should never reach this point I think
                std::cout << "Match not found with id: " << match_id << std::endl;
                // TODO: KILL THIS CORRUPTED CLIENT
                continue;
            } catch (const MatchAlreadyStarted& err) {
                // It should never reach this point I think
                std::cout << "Match already started with id: " << match_id << std::endl;
                // TODO: KILL THIS CORRUPTED CLIENT
                continue;
            } catch (const MapNotFound& err) {
                // It should never reach this point I think
                std::cout << "Map not found with name: " << command.get_map_name() << std::endl;
                // TODO: KILL THIS CORRUPTED CLIENT
                continue;
            }
        } else if (command.get_code() == CASE_NUMBER_OF_PLAYERS) {
            uint8_t number_of_players = monitor_matches.get_number_of_players(match_id);
            Command command_to_send(CASE_NUMBER_OF_PLAYERS, match_id, {""}, number_of_players);
            protocol.send_command(command_to_send);
        }
    }
}

void User::handle_match() {
    while (protocol.is_connected()) {
        std::shared_ptr<GameCommand> game_command = protocol.recv_game_command();

        // CHANGE THIS TO ^^^^!!!!! 
        // std::shared_ptr<GameCommand> game_command = protocol.recv_game_command(worms_ids[0]);
        queue_match->push(game_command);
    }
}

void User::handle_lobby() {
    while (protocol.is_connected()) {
        Command command = protocol.recv_command();
        if (interpretate_command_in_lobby(command)) {
            break;
        }
    }
}

bool User::interpretate_command_in_lobby(Command& command) {
    bool in_match = false;
    char code;
    match_id = command.get_match_id();
    std::vector<std::string> map_names({});
    uint8_t number_of_players = 0;
    switch (command.get_code()) {
        case CASE_CREATE: {
            try {
                queue_match = monitor_matches.create_match(sender->get_queue(),
                command.get_match_id(), number_of_players, map_names, my_army_id);
                in_match = true;
                is_creator = true;
                code = CASE_CREATE;
                std::cout << "Match created with id: " << match_id << std::endl;
            } catch (const MatchAlreadyExists& err) {
                code = CASE_MATCH_ALREADY_EXISTS;
                std::cout << "Match already exists with id: " << command.get_match_id() << std::endl;
            }
            Command command_to_send(code, match_id, map_names, number_of_players);
            protocol.send_command(command_to_send);
            break;
        }
        case CASE_JOIN: {
            try {
                queue_match = monitor_matches.join_match(sender->get_queue(), command.get_match_id(), number_of_players, map_names, my_army_id);
                in_match = true;
                code = CASE_JOIN;
                std::cout << "Match joined with id: " << command.get_match_id() << std::endl;
            } catch (const MatchFull& err) {
                code = CASE_MATCH_FULL;
                std::cout << "Match is full with id: " << command.get_match_id() << std::endl;
            } catch (const MatchNotFound& err) {
                code = CASE_MATCH_NOT_FOUND;
                std::cout << "Match not found with id: " << command.get_match_id() << std::endl;
            } catch (const MatchAlreadyStarted& err) {
                code = CASE_MATCH_ALREADY_STARTED;
                std::cout << "Match already started with id: " << command.get_match_id() << std::endl;
            }
            Command command_to_send(code, match_id, map_names, number_of_players);
            protocol.send_command(command_to_send);
            break;
        }
        case CASE_LIST: {
            std::map<uint, std::string> matches_availables = monitor_matches.list_matches();
            Command command_to_send(CASE_LIST, matches_availables);
            protocol.send_command(command_to_send);
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
