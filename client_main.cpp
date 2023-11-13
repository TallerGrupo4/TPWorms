#include <QApplication>
#include <iostream>
#include <sstream>

#include "client_src/client.h"
#include "client_src/match_renderer.h"
#include "client_src/QT/lobby_renderer.h"

#include "mainwindow.h"

// void print_command(const Command& command) {
//     switch (command.code) {
//         // case CASE_CHAT: {
//         //     std::cout << command.msg << std::endl;
//         //     break;
//         // }
//         case CASE_JOIN: {
//             std::cout << "There are " << +command.number_of_players
//                       << " player/s in the match: " << +command.match_id << std::endl;
//             break;
//         }
//         case CASE_CREATE: {
//             std::cout << "Match succesfully created with the code: " << +command.match_id
//                       << std::endl;
//             break;
//         }
//         case CASE_MATCH_FULL: {
//             std::cout << "The match " << +command.match_id
//                       << " already has the maximum number of players."
//                       << " Try again later or join another match." << std::endl;
//             // in_match = false;
//             break;
//         }
//         case CASE_EXIT_SERVER: {
//             std::cout << "The player " << +command.player_index
//                       << " has left the match. "
//                          "There are still "
//                       << +command.number_of_players << " players in the match." << std::endl;
//             break;
//         }
//         case CASE_MATCH_NOT_FOUND: {
//             std::cout << "The match " << +command.match_id << " wan't found. "
//                       << "Try another code or create a new one." << std::endl;
//             // in_match = false;
//             break;
//         }
//         case CASE_MATCH_ALREADY_EXISTS: {
//             std::cout << "The match " << +command.match_id << " Already exists. "
//                       << "Try with another code." << std::endl;
//             // in_match = false;
//             break;
//         }
//         default:
//             // Throw custom error, it should never reach this point!
//             break;
//     }
// }

// void print_snapshot(const Snapshot& snapshot) {
//     if (!snapshot.platforms.empty()) {
//         for (const PlatformSnapshot& platform : snapshot.platforms) {
//             std::cout << "Platform: " << platform.type << std::endl;
//         }
//     }
// }

// void parse_sending_command(Command& command) {
//     std::istringstream str(command.msg);
//     std::string type;
//     str >> type;
//     if (type == CREATE) {
//         command.code = CASE_CREATE;
//         str >> command.match_id;
//     } else if (type == JOIN) {
//         command.code = CASE_JOIN;
//         str >> command.match_id;
//     } else if (type == EXIT) {
//         command.code = CASE_EXIT;
//     } else {
//         command.code = CASE_INVALID;
//     }
// }

// void get_lobby_command(Command &command) {
//     std::cout << "Enter a command: " << std::endl;
//     std::string input;
//     std::getline(std::cin, command.msg);
//     parse_sending_command(command);
// }

// Action parse_sending_action(std::string msg) {
//     std::istringstream str(msg);
//     std::getline(str >> std::ws, msg, '\0');
//     std::cout << "action (it will be a Start anyways): " << msg << std::endl;
//     if (msg == EXIT) {
//         // return ActionExit;
//         return Action(CASE_EXIT);
//     }// else if (msg == _START) ActionStart;
//     return Action();
// }

// Action get_action_in_match() {
//     std::string msg;
//     std::getline(std::cin, msg);
//     return parse_sending_action(msg);
// }

int main(int argc, char* argv[]) {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments." << std::endl;
        return ret;
    }
    Client client(argv[1], argv[2]);
    // bool in_lobby = true;
    // while (in_lobby) {
    //     // Render_lobby();
    //     Command command = INITIALIZE_COMMAND;
    //     get_lobby_command(command);
    //     if (command.code == CASE_EXIT) {
    //         return 0;
    //     }
    //     client.send_lobby_command(command);
    //     command = client.recv_lobby_command();
    //     if (command.code == CASE_JOIN || command.code == CASE_CREATE) {
    //         in_lobby = false;
    //     }
    //     print_command(command);
    // }

    // // In match
    // // MapSnapshot map = client.recv_map();
    // // Render_map(map)
    // client.start();
    // while (client.is_connected()) {
    //     // Render_match();
    //     Action action = get_action_in_match();
    //     if (action.type == CASE_EXIT) {
    //         client.exit();
    //         return 0;
    //     }
    //     client.send_action(action);
    //     // GameSnapshot game_snapshot = client.recv_game_snapshot();
    //     Snapshot snapshot = client.recv_snapshot();
    //     print_snapshot(snapshot);
    // }
    // // Render_match();
    
    // // MatchRenderer match(client);
    // // match.start();
    LobbyRenderer lobby(client);
    int lobby_ret = lobby.start(argc, argv);
    if (lobby_ret != 4) {
        return 0;
    }
    //MatchRenderer match(client);
    //ret = client.start();
    MatchRenderer match(client);
    match.start();
    return ret;
}
