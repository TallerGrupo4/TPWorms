#include "server.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"


Server::Server(const char* port): socket(port), monitor_matches() {}

void Server::run() {
    while (true) {
        try {
            Socket client_skt = socket.accept();
            clients.push_back(
                    std::make_unique<ServerClient>(std::move(client_skt), monitor_matches));
            clients.back()->start();
            free_dead_clients();
        } catch (const LibError& err) {
            if (is_dead) {
                kill_clients();
                break;
            } else {
                std::cout << R"(Something went wrong and \
                    an exception was caught in the server: )"
                          << err.what() << "\n";
            }
        } catch (...) {
            std::cerr << R"(Something went wrong and \
                an unknown exception was caught in the server: )"
                      << "\n";
        }
    }
}


void Server::free_dead_clients() {
    for (auto clients_it = clients.begin(); clients_it != clients.end(); clients_it++) {
        if ((*clients_it)->is_dead()) {
            (*clients_it)->join();
            clients_it = clients.erase(clients_it);
        }
    }
}

void Server::kill_clients() {
    for (auto clients_it = clients.begin(); clients_it != clients.end(); ++clients_it) {
        if (!(*clients_it)->is_dead()) {
            (*clients_it)->stop();
        }
        (*clients_it)->join();
    }
    monitor_matches.stop();
}

void Server::stop() {
    try {
        is_dead = true;
        socket.shutdown(SHUT_RDWR);
        socket.close();
    } catch (const std::exception& err) {
        std::cerr << R"(Something went wrong and \
            an exception was caught in the server: )"
                  << err.what() << std::endl;
    } catch (...) {
        std::cerr << R"(Something went wrong and \
            an unknown exception was caught in the server: )"
                  << std::endl;
    }
}

Server::~Server() {}
