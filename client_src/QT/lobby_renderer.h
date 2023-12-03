#ifndef LOBBY_RENDERER_H
#define LOBBY_RENDERER_H

#include <exception>
#include <iostream>
#include <QApplication>
#include <QMetaType>

#include "mainwindow.h"
#include "../client.h"
#include "../constantes_cliente.h"

class LobbyRenderer {
private:
    Client& client;
    Snapshot map_snapshot;

public:
    explicit LobbyRenderer(Client& client);
    Snapshot get_received_map();
    bool start(int argc, char* argv[]);
};
#endif  // LOBBY_RENDERER_H