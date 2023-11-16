#include <box2d/box2d.h>

#include "server_src/server.h"

int main(int argc, char* argv[]) {

    int ret = 1;
    try {
        if (argc != 2) {
            std::cerr << "Bad program call. Expected " << argv[0] << " with 1 argument\n"
                      << "E.g.: ./server 8080 \n";
            return ret;
        }
        // argv[2] == PATH
        // Read folder from PATH 
        std::vector<std::string> routes = {"../external/maps/map1.yaml"};
        Server server(argv[1], routes);
        server.start();
        std::string line;
        for (line = ""; line != "q"; std::cin >> line) {}
        server.stop();
        server.join();
        ret = 0;
        return ret;
    } catch (const std::exception& e) {
        std::cerr << "Something went wrong and an exception was caught in server_main: " << e.what()
                  << std::endl;
        return ret;
    } catch (...) {
        std::cerr << R"(Something went wrong and an unknown exception was caught in server_main.)"
                  << std::endl;
        return ret;
    }
}
