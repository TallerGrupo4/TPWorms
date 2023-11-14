#ifndef LOBBY_RENDERER_H
#define LOBBY_RENDERER_H

#include <exception>
#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "../client.h"
#include "../constantes_cliente.h"

class LobbyRenderer {
private:
    Client& client;

    // bool handleEvents(Worm& player);

    // void render(SDL2pp::Renderer& renderer, Worm& player);

    // void update(Worm& player, float dt);

public:
    explicit LobbyRenderer(Client& client);

    bool start(int argc, char* argv[]);
};
#endif  // LOBBY_RENDERER_H