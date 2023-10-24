#include <iostream>
#include "common_src/class0.h"
#include "mainwindow.h"
#include <qt5/QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    std::cout << "Hola mundo" << std::endl;
    Class0 c0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}