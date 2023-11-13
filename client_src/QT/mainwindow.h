#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qt5/QtWidgets/QMainWindow>

#include "../client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Client& client, bool& exit_succesful);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    Client& client;
    bool& exit_succesful;
    void joinMatch();
    void createMatch();
};
#endif  // MAINWINDOW_H
