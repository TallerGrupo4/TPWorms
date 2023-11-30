#include <QApplication>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "client_src/client.h"
#include "client_src/match_renderer.h"
#include "client_src/QT/lobby_renderer.h"

#include "mainwindow.h"

int main(int argc, char* argv[]) { try {
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments." << std::endl;
        return EXIT_FAILURE;
    }
    Client client(argv[1], argv[2]);
    LobbyRenderer lobby(client);
    if (!lobby.start(argc, argv)) {
        client.exit();
        return EXIT_SUCCESS;
    }
    MatchRenderer match(client, lobby.get_received_map());
    match.start();
    return EXIT_SUCCESS;
    } catch (std::exception& e) {
        // If case of error, print it and exit with error
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
