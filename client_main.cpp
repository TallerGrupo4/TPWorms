#include <QApplication>
#include <iostream>

#include "client_src/client.h"
#include "client_src/match_renderer.h"
#include "common_src/constants.h"
#include "common_src/liberror.h"
#include "common_src/socket.h"

#include "mainwindow.h"

int main(int argc, char* argv[]) {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments.\n";
        return ret;
    }
    MatchRenderer match;
    match.start();
    Client client(argv[1], argv[2]);
    ret = client.start();
    return ret;
}
