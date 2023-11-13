#include "lobby_renderer.h"

LobbyRenderer::LobbyRenderer(Client& client) : client(client) {}

int LobbyRenderer::start(int argc, char* argv[]) {
    QApplication app(argc,argv);
    bool exit_succeful;
    MainWindow w(client,exit_succeful);
    w.show();
    app.exec();
    return exit_succeful;
}