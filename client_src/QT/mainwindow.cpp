#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //ui->Label_BackgroundImage->setPixmap(QPixmap(":/main_menu.png"));
    
    std::string path_to_img(__FILE__);
    path_to_img = path_to_img.substr(0,path_to_img.size()-14);
    path_to_img = path_to_img + "main_menu.jpg";
    ui->Label_BackgroundImage->setPixmap(QPixmap(path_to_img.data()));
}

MainWindow::~MainWindow() { delete ui; }
