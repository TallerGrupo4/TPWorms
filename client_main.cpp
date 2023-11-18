#include <QApplication>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "client_src/client.h"
#include "client_src/match_renderer.h"
#include "client_src/QT/lobby_renderer.h"

#include "mainwindow.h"

void print_command(const Command& command) {
    switch (command.get_code()) {
        // case CASE_CHAT: {
        //     std::cout << command.msg << std::endl;
        //     break;
        // }
        case CASE_JOIN: {
            std::cout << "There are " << +command.get_number_of_players()
                      << " player/s in the match: " << +command.get_match_id() << std::endl;
            std::cout << "My worm id is: " << +command.get_worm_id() << std::endl;

            break;
        }
        case CASE_CREATE: {
            std::cout << "Match succesfully created with the code: " << +command.get_match_id()
                      << std::endl;
            std::cout << "My worm id is: " << +command.get_worm_id() << std::endl;
            break;
        }
        case CASE_MATCH_FULL: {
            std::cout << "The match " << +command.get_match_id()
                      << " already has the maximum number of players."
                      << " Try again later or join another match." << std::endl;
            // in_match = false;
            break;
        }
        case CASE_EXIT_SERVER: {
            std::cout << "A player has left the match." << std::endl;
            break;
        }
        case CASE_MATCH_NOT_FOUND: {
            std::cout << "The match " << +command.get_match_id() << " wan't found. "
                      << "Try another code or create a new one." << std::endl;
            // in_match = false;
            break;
        }
        case CASE_MATCH_ALREADY_EXISTS: {
            std::cout << "The match " << +command.get_match_id() << " Already exists. "
                      << "Try with another code." << std::endl;
            // in_match = false;
            break;
        }
        case CASE_NUMBER_OF_PLAYERS: {
            std::cout << "There are " << +command.get_number_of_players()
                      << " player/s in the match: " << +command.get_match_id() << std::endl;
            break;
        }
        case CASE_MATCH_ALREADY_STARTED: {
            std::cout << "The match " << +command.get_match_id() << " has already started."
                      << " Try again later or join another match." << std::endl;
            // in_match = false;
            break;
        }
        default:
            // Throw custom error, it should never reach this point!
            break;
    }
}

void print_snapshot(const Snapshot& snapshot) {
    if (!snapshot.platforms.empty()) {
        for (const PlatformSnapshot& platform : snapshot.platforms) {
            std::cout << "Platform: " << +platform.type << std::endl;
        }
    }
}

Command parse_sending_command(std::string input) {
    std::istringstream str(input);
    std::string type;
    str >> type;
    char code;
    uint match_id;
    if (type == CREATE) {
        code = CASE_CREATE;
        str >> match_id;
    } else if (type == JOIN) {
        code = CASE_JOIN;
        str >> match_id;
    } else if (type == EXIT) {
        code = CASE_EXIT;
    } else {
        code = CASE_INVALID;
    }
    return Command(code, match_id);
}

Command parse_sending_pseudo_command(std::string input) {
    std::istringstream str(input);
    std::string type;
    str >> type;
    char code;
    uint match_id = DEFAULT;
    if (type == _START) {
        code = CASE_START;
    } else if (type == EXIT) {
        code = CASE_EXIT;
    } else if (type == "Refresh") {
        code = CASE_NUMBER_OF_PLAYERS;
    } else {
        code = CASE_INVALID;
    }
    return Command(code, match_id);
}

Command get_pseudo_lobby_command() {
    std::cout << "Enter a command: " << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return parse_sending_pseudo_command(input);
}


Command get_lobby_command() {
    std::cout << "Enter a command: " << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return parse_sending_command(input);
}

std::shared_ptr<Action> parse_sending_action(std::string msg) {
    std::istringstream str(msg);
    std::getline(str >> std::ws, msg, '\0');
    std::cout << "action (it will be a Start anyways): " << msg << std::endl;
    if (msg == EXIT) {
        return std::make_shared<ActionExit>();
    }// else if (msg == _START) ActionStart;
    // return Command(CASE_START, DEFAULT);
    // return std::make_shared<ActionStart>();
    return std::make_shared<Action>();
}

std::shared_ptr<Action> get_action_in_match() {
    std::string msg;
    std::getline(std::cin, msg);
    return parse_sending_action(msg);
}

int dummy_client(Client& client) {
    bool in_lobby = true;
    bool is_creator = false;
    while (in_lobby) {
        // Render_lobby();
        Command command = get_lobby_command();
        if (command.get_code() == CASE_EXIT) {
            return 0;
        }
        client.send_lobby_command(command);
        Command command_received = client.recv_lobby_command();
        if (command_received.get_code() == CASE_JOIN || command_received.get_code() == CASE_CREATE) {
            in_lobby = false;
            if (command_received.get_code() == CASE_CREATE) {
                std::cout << "You are the creator of the match." << std::endl;
                is_creator = true;
            }
        }
        print_command(command_received);
    }
    

    // In pseudo-lobby
    bool pseudo_lobby = true;
    while (pseudo_lobby) {
        // Render_pseudo_lobby();
        if (is_creator) {
            Command command = get_pseudo_lobby_command();
            if (command.get_code() == CASE_EXIT) {
                return 0;
            }
            if (command.get_code() == CASE_START) {
                pseudo_lobby = false;
                client.send_lobby_command(command);
            std::cout << "Wating for map..." << std::endl;
                Snapshot snapshot = client.recv_map();
                std::cout << "Wating for map to be loaded in creator..." << std::endl;
                print_snapshot(snapshot);
            } else if (command.get_code() == CASE_NUMBER_OF_PLAYERS) {
                client.send_lobby_command(command);
                Command command_received = client.recv_lobby_command();
                print_command(command_received);
            }
        } else {
            std::cout << "Wating for map..." << std::endl;
            Snapshot snapshot = client.recv_map();
            // Load map
            // Render_map();
            pseudo_lobby = false; // break
            std::cout << "Wating for map to be loaded..." << std::endl;
            print_snapshot(snapshot);
        }
    }


    // In match
    client.start();
    while (client.is_connected()) {
        // Render_match();
        std::shared_ptr<Action> action = get_action_in_match();
        if (action->is_exit()) {
            client.exit();
            return 0;
        }
        client.send_action(action);
        // GameSnapshot game_snapshot = client.recv_game_snapshot();
        Snapshot snapshot;
        while (client.recv_snapshot(snapshot)) {
            print_snapshot(snapshot);
        }
        // Snapshot snapshot = client.recv_snapshot();
    }

    return 0;
}

int main(int argc, char* argv[]) { try {
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments." << std::endl;
        return EXIT_FAILURE;
    }
    Client client(argv[1], argv[2]);
    // return dummy_client(client);
    LobbyRenderer lobby(client);
    if (!lobby.start(argc, argv)) {
        return EXIT_SUCCESS;
    }
    MatchRenderer match(client);
    match.start();
    return EXIT_SUCCESS;
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    
    // // Render_match();
    
    // // MatchRenderer match(client);
    // // match.start();
    //MatchRenderer match(client);
    //ret = client.start();
}
