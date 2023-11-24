#include "mainwindow.h"

#include <cstdint>
#include <string>
#include <qwidget.h>
#include <iostream>
#include <QStringListModel>
#include <vector>

#include "ui_mainwindow.h"

MainWindow::MainWindow(Client& client, bool& exit_succesful, Snapshot& map_snapshot): QMainWindow(nullptr), ui(new Ui::MainWindow), client(client), exit_succesful(exit_succesful), map_recieved(map_snapshot) {
    ui->setupUi(this);
    exit_succesful = false;
    // ui->Label_BackgroundImage->setPixmap(QPixmap(":/main_menu.png"));

    std::string path_to_img(ASSETS_PATH);
    path_to_img = path_to_img + "/main_menu.png";
    ui->Label_BackgroundImage->setPixmap(QPixmap(path_to_img.data()));
    ui->MatchOptionsFrame->setVisible(true);
    ui->MatchOptionsFrame->setEnabled(true);
    ui->PreMatchFrame->setVisible(false);
    ui->PreMatchFrame->setEnabled(false);

    // AGARRO LAS LISTAS DE LAS PARTIDAS
    Command cmd(CASE_LIST);
    client.send_lobby_command(cmd);

    Command recv_cmd = client.recv_lobby_command();
    std::map<uint, std::string> matches_available = recv_cmd.get_available_matches();
    // Create a unique_ptr for the QStringListModel
    std::unique_ptr<QStringListModel> model = std::make_unique<QStringListModel>();
    // Set each available match in the model
    QStringList matchesList;
    for (auto it = matches_available.begin(); it != matches_available.end(); ++it) {
        QString match_id = QString::number(it->first);
        QString match_name = QString::fromStdString(it->second);
        QString match = match_id + " - " + match_name;
        matchesList << match;
    }
    // Set the QStringList as the model data
    model->setStringList(matchesList);
    // Set the model on the QListView
    ui->MatchesListView->setModel(model.release()); // Release ownership to QListView


    QObject::connect(ui->JoinMatchButton, &QPushButton::clicked,
                     this, &MainWindow::joinMatch);
    
    QObject::connect(ui->CreateMatchButton, &QPushButton::clicked,
                     this, &MainWindow::createMatch);
    QObject::connect(ui->RefreshListButton, &QPushButton::clicked,
                    this, &MainWindow::refreshMatchesList);

    QObject::connect(ui->StartMatchButton, &QPushButton::clicked,
                    this, &MainWindow::startMatch);

    QObject::connect(ui->RefreshButton, &QPushButton::clicked,
                    this, &MainWindow::refreshPlayersInPreMatch);
}

void MainWindow::refreshMatchesList() {
    Command cmd(CASE_LIST);
    client.send_lobby_command(cmd);
    Command recv_cmd = client.recv_lobby_command();
    std::map<uint, std::string> matches_available = recv_cmd.get_available_matches();

    
    // Create a unique_ptr for the QStringListModel
    std::unique_ptr<QStringListModel> model = std::make_unique<QStringListModel>();

    // Set each available match in the model
    QStringList matchesList;
    for (auto it = matches_available.begin(); it != matches_available.end(); ++it) {
        QString match_id = QString::number(it->first);
        QString match_name = QString::fromStdString(it->second);
        QString match = match_id + " - " + match_name;
        matchesList << match;
    }

    // Set the QStringList as the model data
    model->setStringList(matchesList);

    // Set the model on the QListView
    ui->MatchesListView->setModel(model.release()); // Release ownership to QListView
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
            uint match_id = code_string.toUInt(&ok);
            if(!ok) {
                ui->JoinMatchLineEdit->clear();
                ui->JoinMatchLineEdit->setText("Error: Unable to convert code");
            }
            Command cmd(CASE_JOIN, match_id);
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
                if(match_id != recv_cmd.get_match_id()) {
                    std::cout << "MATCH CODE INCORRECT" << std::endl;
                    exit_succesful = false;
                    this->close();
                }
                match_code = match_id;
                handle_pre_match(recv_cmd.get_map_names(), recv_cmd.get_number_of_players(), false);
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
            uint match_id = code_string.toUInt(&ok);
            if(!ok) {
                ui->CreateMatchLineEdit->clear();
                ui->CreateMatchLineEdit->setText("Error: Unable to convert code");
            }
            Command cmd(CASE_CREATE, match_id);
            client.send_lobby_command(cmd);
            Command recv_cmd = client.recv_lobby_command();
            switch (recv_cmd.get_code()) {
                case CASE_MATCH_ALREADY_EXISTS:
                    ui->CreateMatchLineEdit->clear();
                    ui->CreateMatchLineEdit->setText("Error: Match already exist");
                    break;

                case CASE_CREATE:
                    if(match_id != recv_cmd.get_match_id()) {
                        std::cout << "MATCH CODE INCORRECT" << std::endl;
                        exit_succesful = false;
                        this->close();
                    }
                    match_code = match_id;
                    handle_pre_match(recv_cmd.get_map_names(), recv_cmd.get_number_of_players(), true);
                    break;
                }
            
        } else {
            ui->CreateMatchLineEdit->clear();
            ui->CreateMatchLineEdit->setText("Error: Code is not numerical");
        }
    }
}

void MainWindow::startMatch() {
    QString map_name = ui->SelectMapComboBox->currentText();

    Command sending_command(CASE_START,match_code,map_name.toStdString());
    client.send_lobby_command(sending_command);
    map_recieved = client.recv_map();
    exit_succesful = true;
    this->close();
}

void MainWindow::refreshPlayersInPreMatch() {
    Command cmd(CASE_NUMBER_OF_PLAYERS);
    client.send_lobby_command(cmd);
    Command recv_cmd = client.recv_lobby_command();
    switch (recv_cmd.get_number_of_players()) {
        case 4:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString("Player 2"));
            ui->Player3Label->setText(QString("Player 3"));
            ui->Player4Label->setText(QString("Player 4"));
            break;
        case 3:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString("Player 2"));
            ui->Player4Label->setText(QString(""));
            ui->Player3Label->setText(QString("Player 3"));
            break;
        case 2:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            ui->Player2Label->setText(QString("Player 2"));
            break;
        case 1:
            ui->Player2Label->setText(QString(""));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            ui->Player1Label->setText(QString("Player 1"));
            break;
        default:
            break;
    }
}

void MainWindow::handle_pre_match(std::vector<std::string> map_names, uint8_t number_of_players, bool creator) {
    ui->MatchOptionsFrame->setVisible(false);
    ui->MatchOptionsFrame->setEnabled(false);
    ui->PreMatchFrame->setVisible(true);
    ui->PreMatchFrame->setEnabled(true);
    ui->StartMatchButton->setEnabled(true);

    ui->PreMatchLabel->setText(QString::number(match_code));
    QStringList mapNamesList;
    for (auto it = map_names.begin(); it != map_names.end(); ++it) {
        mapNamesList << QString::fromStdString(*it);
    }
    ui->SelectMapComboBox->addItems(mapNamesList);
    switch (number_of_players) {
        case 4:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString("Player 2"));
            ui->Player3Label->setText(QString("Player 3"));
            ui->Player4Label->setText(QString("Player 4"));
            break;
        case 3:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString("Player 2"));
            ui->Player4Label->setText(QString(""));
            ui->Player3Label->setText(QString("Player 3"));
            break;
        case 2:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            ui->Player2Label->setText(QString("Player 2"));
            break;
        case 1:
            ui->Player2Label->setText(QString(""));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            ui->Player1Label->setText(QString("Player 1"));
            break;
        default:
            break;
    }

    if(!creator) {
        ui->StartMatchButton->setEnabled(false);
        ui->RefreshButton->setEnabled(false);
        map_recieved = client.recv_map();
    }
}

MainWindow::~MainWindow() { delete ui; }
