#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include <string>
#include <vector>

#include <qt5/QtWidgets/QMainWindow>

#include "../../common_src/custom_errors.h"
#include "../client.h"

#include "lobby_constants.h"
#include "worker.h"

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

public slots:
    void onMatchesListViewClicked(const QModelIndex& index);

private:
    Ui::MainWindow* ui;
    QMediaPlayer player;
    QMediaPlaylist playlist;
    Client& client;
    bool& exit_succesful;
    uint match_code = 0;
    Snapshot& map_recieved;
    Worker* worker;
    QThread* thread;

    void joinMatch();
    void createMatch();
    void startMatch();
    void refreshPlayersInPreMatch();
    void refreshMatchesList();
    void handle_pre_match(std::vector<std::string> map_names, uint8_t number_of_players,
                          bool creator);
    void updateMap(const Snapshot& map);
};
#endif  // MAINWINDOW_H
