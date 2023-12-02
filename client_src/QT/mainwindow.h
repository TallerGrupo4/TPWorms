#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qt5/QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "../client.h"
#include "lobby_constants.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Client& client, bool& exit_succesful, Snapshot& map_snapshot);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QMediaPlayer player;
    QMediaPlaylist playlist;
    Client& client;
    bool& exit_succesful;
    uint match_code = 0;
    Snapshot& map_recieved;

    void joinMatch();
    void createMatch();
    void startMatch();
    void refreshPlayersInPreMatch();
    void refreshMatchesList();
    void handle_pre_match(std::vector<std::string> map_names, uint8_t number_of_players, bool creator);
};
#endif  // MAINWINDOW_H
