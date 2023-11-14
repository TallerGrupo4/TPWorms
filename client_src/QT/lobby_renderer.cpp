#include "lobby_renderer.h"

LobbyRenderer::LobbyRenderer(Client& client) : client(client) {}

bool LobbyRenderer::start(int argc, char* argv[]) {
    QApplication app(argc,argv);
    bool exit_succesfull = false;
    MainWindow w(client,exit_succesfull);
    w.show();
    app.exec();
    return exit_succesfull;
}