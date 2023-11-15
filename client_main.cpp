#include <QApplication>
#include <iostream>
#include <sstream>

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
            break;
        }
        case CASE_CREATE: {
            std::cout << "Match succesfully created with the code: " << +command.get_match_id()
                      << std::endl;
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

Command get_lobby_command() {
    std::cout << "Enter a command: " << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return parse_sending_command(input);
}

Action parse_sending_action(std::string msg) {
    std::istringstream str(msg);
    std::getline(str >> std::ws, msg, '\0');
    std::cout << "action (it will be a Start anyways): " << msg << std::endl;
    if (msg == EXIT) {
        // return ActionExit;
        return Action(CASE_EXIT);
    }// else if (msg == _START) ActionStart;
    return Action();
}

Action get_action_in_match() {
    std::string msg;
    std::getline(std::cin, msg);
    return parse_sending_action(msg);
}

int dummy_client(Client& client) {
    bool in_lobby = true;
    uint8_t worm_id = DEFAULT;
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
            worm_id = command.worm_id;
        }
        print_command(command_received);
    }
    std::cout << "My worm id is: " << +worm_id << std::endl;
    // In match
    client.start();
    while (client.is_connected()) {
        // Render_match();
        Action action = get_action_in_match();
        if (action.type == CASE_EXIT) {
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

int main(int argc, char* argv[]) {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments." << std::endl;
        return ret;
    }
    Client client(argv[1], argv[2]);
    
    // return dummy_client(client);

    
    // // Render_match();
    
    // // MatchRenderer match(client);
    // // match.start();
    //MatchRenderer match(client);
    //ret = client.start();


    LobbyRenderer lobby(client);
    if (!lobby.start(argc, argv)) {
        return EXIT_SUCCESS;
    }
    MatchRenderer match(client);
    ret = match.start();
    return ret;
}
