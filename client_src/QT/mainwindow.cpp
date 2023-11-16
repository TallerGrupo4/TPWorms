#include "mainwindow.h"

#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(Client& client, bool& exit_succesful): QMainWindow(nullptr), ui(new Ui::MainWindow), client(client), exit_succesful(exit_succesful) {
    ui->setupUi(this);
    exit_succesful = false;
    // ui->Label_BackgroundImage->setPixmap(QPixmap(":/main_menu.png"));

    std::string path_to_img(__FILE__);
    path_to_img = path_to_img.substr(0, path_to_img.size() - 14);
    path_to_img = path_to_img + "main_menu.jpg";
    ui->Label_BackgroundImage->setPixmap(QPixmap(path_to_img.data()));
    
    QObject::connect(ui->JoinMatchButton, &QPushButton::clicked,
                     this, &MainWindow::joinMatch);
    
    QObject::connect(ui->CreateMatchButton, &QPushButton::clicked,
                     this, &MainWindow::createMatch);
}

void MainWindow::joinMatch() {
    QString code_string = ui->JoinMatchLineEdit->text();
    if (code_string.size() > 4) {
        ui->JoinMatchLineEdit->clear();
        ui->JoinMatchLineEdit->setText("Error: Max of 4 digits");
    } else if (code_string.isEmpty()) {
        ui->JoinMatchLineEdit->clear();
        ui->JoinMatchLineEdit->setText("Error: Code is Empty");
    } else {
        QRegExp re("\\d*");
        if (re.exactMatch(code_string)) {
            bool ok;
            int match_code = code_string.toUInt(&ok);
            if(!ok) {
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Unable to convert code");
            }
            Command cmd(CASE_JOIN, match_code);
            client.send_lobby_command(cmd);
            Command recv_cmd = client.recv_lobby_command();
            switch (recv_cmd.get_code()) {
            case CASE_MATCH_FULL:
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Match full");
                break;
            
            case CASE_MATCH_NOT_FOUND:
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Match not found");
                break;

            case CASE_JOIN:
                exit_succesful = true;
                this->close();
                break;
            }
            
        } else {
            ui->JoinMatchLineEdit->clear();
            ui->JoinMatchLineEdit->setText("Error: Code is not numerical");
        }
    }
}

void MainWindow::createMatch() {
QString code_string = ui->CreateMatchLineEdit->text();
    if (code_string.size() > 4) {
        ui->CreateMatchLineEdit->clear();
        ui->CreateMatchLineEdit->setText("Error: Max of 4 digits");
    } else if (code_string.isEmpty()) {
        ui->CreateMatchLineEdit->clear();
        ui->CreateMatchLineEdit->setText("Error: Code is Empty");
    } else {
        QRegExp re("\\d*");
        if (re.exactMatch(code_string)) {
            bool ok;
            uint match_code = code_string.toUInt(&ok);
            if(!ok) {
                ui->CreateMatchLineEdit->clear();
                ui->CreateMatchLineEdit->setText("Error: Unable to convert code");
            }
            Command cmd(CASE_CREATE, match_code);
            client.send_lobby_command(cmd);
            Command recv_cmd = client.recv_lobby_command();
            switch (recv_cmd.get_code()) {
            case CASE_MATCH_ALREADY_EXISTS:
                ui->CreateMatchLineEdit->clear();
                ui->CreateMatchLineEdit->setText("Error: Match already exist");
                break;

            case CASE_CREATE:
                Command cmd2(CASE_START,match_code,"hola");
                client.send_lobby_command(cmd2);
                exit_succesful = true;
                this->close();
                break;
            }
            
        } else {
            ui->CreateMatchLineEdit->clear();
            ui->CreateMatchLineEdit->setText("Error: Code is not numerical");
        }
    }
}

// Create a START botton in qt that sends a StartCommand to the server
// client.send_action(StartAction)

MainWindow::~MainWindow() { delete ui; }
