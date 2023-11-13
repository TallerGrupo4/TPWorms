#include "mainwindow.h"

#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(Client& client): QMainWindow(nullptr), ui(new Ui::MainWindow), client(client) {
    ui->setupUi(this);
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
            Command cmd = INITIALIZE_COMMAND;
            cmd.code = CASE_JOIN;            //Constructor del struct command (atributos con const)
            cmd.match_id = match_code;
            client.send_lobby_command(cmd);
            Command recv_cmd = client.recv_lobby_command();
            switch (recv_cmd.code) {
            case CASE_MATCH_FULL:
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Match full");
                break;
            
            case CASE_MATCH_NOT_FOUND:
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Match not found");
                break;

            case CASE_START:
                this->close();
                qApp->exit(4);
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
            int match_code = code_string.toUInt(&ok);
            if(!ok) {
                ui->CreateMatchLineEdit->clear();
                ui->CreateMatchLineEdit->setText("Error: Unable to convert code");
            }
            Command cmd = INITIALIZE_COMMAND;
            cmd.code = CASE_CREATE;
            cmd.match_id = match_code;
            client.send_lobby_command(cmd);
            Command recv_cmd = client.recv_lobby_command();
            switch (recv_cmd.code) {
            case CASE_MATCH_ALREADY_EXISTS:
                ui->CreateMatchLineEdit->clear();
                ui->CreateMatchLineEdit->setText("Error: Match already exist");
                break;

            case CASE_START:
                this->close();
                qApp->exit(4);
                break;
            }
            
        } else {
            ui->CreateMatchLineEdit->clear();
            ui->CreateMatchLineEdit->setText("Error: Code is not numerical");
        }
    }
}

MainWindow::~MainWindow() { delete ui; }
