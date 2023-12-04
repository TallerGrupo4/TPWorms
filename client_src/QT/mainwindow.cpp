#include "mainwindow.h"

#include <cstdint>
#include <string>
#include <qwidget.h>
#include <iostream>
#include <QStringListModel>
#include <vector>

#include "ui_mainwindow.h"

MainWindow::MainWindow(Client& client, bool& exit_succesful, Snapshot& map_snapshot): QMainWindow(nullptr), ui(new Ui::MainWindow), player(this), playlist(this), client(client), exit_succesful(exit_succesful), map_recieved(map_snapshot),
                        worker(new Worker(client)), thread(new QThread) {
    ui->setupUi(this);
    exit_succesful = false;
    
    std::string path_to_bkgrnd_img(MAIN_MENU_BACKGROUND_PATH);
    ui->Label_BackgroundImage->setPixmap(QPixmap(path_to_bkgrnd_img.data()));


    QUrl url_to_bkgrnd_music = QUrl::fromLocalFile(QString::fromStdString(MAIN_MENU_BACKGROUND_MUSIC_PATH));
    QUrl url_to_bkgrnd_music_2 = QUrl::fromLocalFile(QString::fromStdString(MAIN_MENU_BACKGROUND_MUSIC_2_PATH));

    
    playlist.addMedia(url_to_bkgrnd_music);
    playlist.addMedia(url_to_bkgrnd_music_2);
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
    player.setPlaylist(&playlist);
    player.play();

    ui->MatchOptionsFrame->setVisible(true);
    ui->MatchOptionsFrame->setEnabled(true);
    ui->PreMatchFrame->setVisible(false);
    ui->PreMatchFrame->setEnabled(false);

    ui->ErrorJoinningMatchLabel->setStyleSheet("QLabel { color : red; }");
    ui->ErrorCreatingMatchLabel->setStyleSheet("QLabel { color : red; }");

    // AGARRO LAS LISTAS DE LAS PARTIDAS
    Command cmd(CASE_LIST);
    try {
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

        this->worker->moveToThread(this->thread);
        
        QObject::connect(thread, &QThread::started, worker, &Worker::doWork);
        QObject::connect(worker, &Worker::workFinished, this, &MainWindow::updateMap);
        QObject::connect(thread, &QThread::finished, worker, &Worker::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

        QObject::connect(ui->MatchesListView, &QListView::clicked,
                    this, &MainWindow::onMatchesListViewClicked);

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
    } catch (const LostConnection& e) {
        std::cerr << "Lost connection in receiving lobbies lists" << std::endl;
        exit_succesful = false;
        this->close();
    }
}

void MainWindow::onMatchesListViewClicked(const QModelIndex& index) {
    QString fullText = index.data(Qt::DisplayRole).toString();
    QString idText = fullText.split(" - ").first();
    ui->JoinMatchLineEdit->setText(idText);
}

void MainWindow::updateMap(const Snapshot& map) {
    map_recieved = map;
    exit_succesful = true;
    this->close();
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
        ui->ErrorJoinningMatchLabel->clear();
        ui->ErrorJoinningMatchLabel->setText("Error: Max of 4 digits");
    } else if (code_string.isEmpty()) {
        ui->JoinMatchLineEdit->clear();
        ui->ErrorJoinningMatchLabel->clear();
        ui->ErrorJoinningMatchLabel->setText("Error: Code is Empty");
    } else {
        QRegExp re("\\d*");
        if (re.exactMatch(code_string)) {
            bool ok;
            uint match_id = code_string.toUInt(&ok);
            if(!ok) {
                ui->JoinMatchLineEdit->clear();
                ui->ErrorJoinningMatchLabel->clear();
                ui->ErrorJoinningMatchLabel->setText("Error: Unable to convert code");
                return;
            }
            Command cmd(CASE_JOIN, match_id);
            try {
                client.send_lobby_command(cmd);
                Command recv_cmd = client.recv_lobby_command();
                switch (recv_cmd.get_code()) {
                case CASE_MATCH_FULL:
                    ui->JoinMatchLineEdit->clear();
                    ui->ErrorJoinningMatchLabel->clear();
                    ui->ErrorJoinningMatchLabel->setText("Error: Match full");
                    break;
                
                case CASE_MATCH_NOT_FOUND:
                    ui->JoinMatchLineEdit->clear();
                    ui->ErrorJoinningMatchLabel->clear();
                    ui->ErrorJoinningMatchLabel->setText("Error: Match not found");
                    break;

                case CASE_JOIN:
                    if(match_id != recv_cmd.get_match_id()) {
                        std::cerr << "MATCH CODE INCORRECT IN JOINING IN LOBBY: RECV FROM COMMAND IS DIFFERENT FROM CLIENT ( match_id: " << match_id << " recv_id: " << recv_cmd.get_match_id() << " )"<< std::endl;
                        exit_succesful = false;
                        this->close();
                    }
                    match_code = match_id;
                    handle_pre_match(recv_cmd.get_map_names(), recv_cmd.get_number_of_players(), false);
                    break;
                case CASE_MATCH_ALREADY_STARTED:
                    ui->JoinMatchLineEdit->clear();
                    ui->ErrorJoinningMatchLabel->clear();
                    ui->ErrorJoinningMatchLabel->setText("Error: Match already started");
                    break;
                }
            } catch (const LostConnection& e) {
                std::cerr << "Lost connection in join match" << std::endl;
                exit_succesful = false;
                this->close();
            }
        } else {
            ui->JoinMatchLineEdit->clear();
            ui->ErrorJoinningMatchLabel->clear();
            ui->ErrorJoinningMatchLabel->setText("Error: Code is not numerical");
        }
    }
}

void MainWindow::createMatch() {
QString code_string = ui->CreateMatchLineEdit->text();
    if (code_string.size() > 4) {
        ui->CreateMatchLineEdit->clear();
        ui->ErrorCreatingMatchLabel->clear();
        ui->ErrorCreatingMatchLabel->setText("Error: Max of 4 digits");
    } else if (code_string.isEmpty()) {
        ui->CreateMatchLineEdit->clear();
        ui->ErrorCreatingMatchLabel->clear();
        ui->ErrorCreatingMatchLabel->setText("Error: Code is Empty");
    } else {
        QRegExp re("\\d*");
        if (re.exactMatch(code_string)) {
            bool ok;
            uint match_id = code_string.toUInt(&ok);
            if(!ok) {
                ui->CreateMatchLineEdit->clear();
                ui->ErrorCreatingMatchLabel->clear();
                ui->ErrorCreatingMatchLabel->setText("Error: Unable to convert code");
                return;
            }
            Command cmd(CASE_CREATE, match_id);
            try {
                client.send_lobby_command(cmd);
                Command recv_cmd = client.recv_lobby_command();
                switch (recv_cmd.get_code()) {
                    case CASE_MATCH_ALREADY_EXISTS:
                        ui->CreateMatchLineEdit->clear();
                        ui->ErrorCreatingMatchLabel->clear();
                        ui->ErrorCreatingMatchLabel->setText("Error: Match already exist");
                        break;

                    case CASE_CREATE:
                        if(match_id != recv_cmd.get_match_id()) {
                            std::cerr << "MATCH CODE INCORRECT IN CREATING IN LOBBY: RECV FROM COMMAND IS DIFFERENT FROM CLIENT ( match_id: " << match_id << " recv_id: " << recv_cmd.get_match_id() << " )"<< std::endl;
                            exit_succesful = false;
                            this->close();
                        }
                        match_code = match_id;
                        handle_pre_match(recv_cmd.get_map_names(), recv_cmd.get_number_of_players(), true);
                        break;
                }
            } catch (const LostConnection& e) {
                std::cerr << "Lost connection in create match" << std::endl;
                exit_succesful = false;
                this->close();
            }
        } else {
            ui->CreateMatchLineEdit->clear();
            ui->ErrorCreatingMatchLabel->clear();
            ui->ErrorCreatingMatchLabel->setText("Error: Code is not numerical");
        }
    }
}

void MainWindow::startMatch() {
    QString map_name = ui->SelectMapComboBox->currentText();

    Command sending_command(CASE_START,match_code,map_name.toStdString());
    try {
        client.send_lobby_command(sending_command);
        map_recieved = client.recv_map();
        exit_succesful = true;
        this->close();
    } catch (const LostConnection& e) {
        std::cerr << "Lost connection in receiving map" << std::endl;
        exit_succesful = false;
        this->close();
    }
}

void MainWindow::refreshPlayersInPreMatch() {
    Command cmd(CASE_NUMBER_OF_PLAYERS);
    try {
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
                ui->Player3Label->setText(QString("Player 3"));
                ui->Player4Label->setText(QString(""));
                break;
            case 2:
                ui->Player1Label->setText(QString("Player 1"));
                ui->Player2Label->setText(QString("Player 2"));
                ui->Player3Label->setText(QString(""));
                ui->Player4Label->setText(QString(""));
                break;
            case 1:
                ui->Player1Label->setText(QString("Player 1"));
                ui->Player2Label->setText(QString(""));
                ui->Player3Label->setText(QString(""));
                ui->Player4Label->setText(QString(""));
                break;
            default:
                break;
        }
        if(recv_cmd.get_number_of_players() > 1) {
            ui->StartMatchButton->setEnabled(true);
        }
    } catch (const LostConnection& e) {
        std::cerr << "Lost connection in pre-match refreshing" << std::endl;
        exit_succesful = false;
        this->close();
    }
}

void MainWindow::handle_pre_match(std::vector<std::string> map_names, uint8_t number_of_players, bool creator) {
    ui->MatchOptionsFrame->setVisible(false);
    ui->MatchOptionsFrame->setEnabled(false);
    ui->PreMatchFrame->setVisible(true);
    ui->PreMatchFrame->setEnabled(true);
    ui->StartMatchButton->setEnabled(false);

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
            ui->Player3Label->setText(QString("Player 3"));
            ui->Player4Label->setText(QString(""));
            break;
        case 2:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString("Player 2"));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            break;
        case 1:
            ui->Player1Label->setText(QString("Player 1"));
            ui->Player2Label->setText(QString(""));
            ui->Player3Label->setText(QString(""));
            ui->Player4Label->setText(QString(""));
            break;
        default:
            break;
    }

    if(!creator) {
        ui->SelectMapComboBox->setEnabled(false);
        ui->StartMatchButton->setEnabled(false);
        ui->RefreshButton->setEnabled(false);
        thread->start();
    }
}

MainWindow::~MainWindow() { 
    thread->quit();
    thread->wait();
    delete ui;
}
