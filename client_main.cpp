#include <QApplication>
#include <iostream>
#include <sstream>

#include "client_src/client.h"
#include "client_src/match_renderer.h"
#include "common_src/constants.h"
#include "common_src/liberror.h"
#include "common_src/socket.h"
#include "common_src/game_command.h"

#include "mainwindow.h"

void print_command(const Command& command) {
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
            // in_match = false;
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
            // in_match = false;
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            std::cout << "The match " << +command.match_id << " Already exists. "
                      << "Try with another code." << std::endl;
            // in_match = false;
            break;
        }
        default:
            // Throw custom error, it should never reach this point!
            break;
    }
}

void print_snapshot(const Snapshot& snapshot) {
    std::cout << snapshot.msg << std::endl;
}

void parse_sending_command(Command& command) {
    std::istringstream str(command.msg);
    std::string type;
    str >> type;
    if (type == CREATE) {
        command.code = CASE_CREATE;
        str >> command.match_id;
    } else if (type == JOIN) {
        command.code = CASE_JOIN;
        str >> command.match_id;
    } else if (type == EXIT) {
        command.code = CASE_EXIT;
    } else {
        command.code = CASE_INVALID;
    }
}

void get_action_in_lobby(Command &command) {
    std::cout << "Enter a command: " << std::endl;
    std::string input;
    std::getline(std::cin, command.msg);
    parse_sending_command(command);
}

void parse_sending_game_command(GameCommand& game_command) {
    std::istringstream str(game_command.msg);
    std::getline(str >> std::ws, game_command.msg, '\0');
    game_command.code = CASE_CHAT;
    std::cout << "Game command: " << game_command.msg << std::endl;
    if (game_command.msg == EXIT) game_command.code = CASE_EXIT;
    if (game_command.msg == START) game_command.code = CASE_START;
}

void get_action_in_match(GameCommand &game_command) {
    // std::cout << "Waiting for a game command: " << std::endl;
    std::getline(std::cin, game_command.msg);
    parse_sending_game_command(game_command);
}

int main(int argc, char* argv[]) {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments." << std::endl;
        return ret;
    }
    Client client(argv[1], argv[2]);
    bool in_lobby = true;
    while (in_lobby) {
        // Render_lobby();
        Command command = INITIALIZE_COMMAND;
        get_action_in_lobby(command);
        if (command.code == CASE_EXIT) {
            return 0;
        }
        client.send_lobby_command(command);
        command = client.recv_lobby_command();
        if (command.code == CASE_JOIN || command.code == CASE_CREATE) {
            in_lobby = false;
        }
        print_command(command);
    }

    // In match
    // MapSnapshot map = client.recv_map();
    // Render_map(map)
    client.start();
    while (client.is_connected()) {
        // Render_match();
        GameCommand game_command;
        get_action_in_match(game_command);
        if (game_command.code == CASE_EXIT) {
            client.exit();
            return 0;
        }
        client.send_game_command(game_command);
        // GameSnapshot game_snapshot = client.recv_game_snapshot();
        Snapshot snapshot = client.recv_snapshot();
        if (snapshot.code != DEFAULT) print_snapshot(snapshot);
    }
    // Render_match();
    
    // MatchRenderer match(client);
    // match.start();
    return ret;
}
