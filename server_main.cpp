#include <box2d/box2d.h>

#include "server_src/config.h"
#include "server_src/server.h"

#include "map_routes.h"

int main(int argc, char* argv[]) {

    int ret = 1;
    try {
        if (argc < 2 || argc > 3) {
            std::cerr << "Bad program call. Expected " << argv[0] << " with 1 or 2 argument/s"
                      << std::endl;
            std::cerr << "E.g.: ./server 8080 " << std::endl;
            std::cerr << "E.g.: ./server 8080 /etc/worms/config.yaml" << std::endl;
            return ret;
        }
        std::string config_path = "/etc/worms/config.yaml";
        if (argc == 3) {
            config_path = argv[2];
        }
        std::string maps_path = "/var/worms/external/maps";
        MapRoutes map_routes(maps_path);
        std::vector<std::string> routes = map_routes.get_routes();
        ConfigSingleton::getInstance(config_path);
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
