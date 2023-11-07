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
            Socket user_skt = socket.accept();
            users.push_back(std::make_unique<User>(std::move(user_skt), monitor_matches));
            users.back()->start();
            free_dead_users();
        } catch (const LibError& err) {
            if (is_dead) {
                kill_users();
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


void Server::free_dead_users() {
    for (auto users_it = users.begin(); users_it != users.end(); users_it++) {
        if ((*users_it)->is_dead()) {
            (*users_it)->join();
            users_it = users.erase(users_it);
        }
    }
}

void Server::kill_users() {
    for (auto users_it = users.begin(); users_it != users.end(); ++users_it) {
        if (!(*users_it)->is_dead()) {
            (*users_it)->stop();
        }
        (*users_it)->join();
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
