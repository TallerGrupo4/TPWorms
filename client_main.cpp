#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include "client_src/client_client.h"
#include "common_src/common_liberror.h"
#include "common_src/common_socket.h"
#include "common_src/constants.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    int ret = 1;
    try {
        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0] << " with 2 arguments.\n";
            return ret;
        }
        Client client(argv[1], argv[2]);
        client.start();
        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cout << "Exception caught in main_client: " << err.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught in main_client." << std::endl;
    }
    return ret;
}
