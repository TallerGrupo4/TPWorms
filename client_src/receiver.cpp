#include "receiver.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


ClientReceiver::ClientReceiver(Socket& skt, std::shared_ptr<Queue<Command>> _queue_lobby, std::shared_ptr<Queue<Command>> _queue_match, std::atomic<bool>& _in_match, std::atomic<bool>& _is_dead):
        socket(skt), queue_lobby(_queue_lobby), queue_match(_queue_match), in_match(_in_match), parser(), protocol(socket, parser), is_dead(_is_dead) {}


void ClientReceiver::run() {
    try {
        while (protocol.is_connected() && !is_dead) {
            if (in_match) {
                handle_match();
            } else {
                handle_lobby();
            }
        }
    } catch (const LibError& e) {
        std::cout << "ClientReceiver has finished because LibError: " << e.what() << std::endl;
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the queue has been closed.
        // std::cout << "ClientReceiver has finished because ClosedQueue: " << e.what() <<
        // std::endl;
    } catch (...) {
        std::cerr << "ClientReceiver has finished because of an unknown error" << std::endl;
    }
}

void ClientReceiver::handle_lobby() {
    Command command = INITIALIZE_COMMAND;
    protocol.recv_lobby(command);
    if (command.code == CASE_JOIN || command.code == CASE_CREATE)
        in_match = true;
    queue_lobby->push(command);
}

void ClientReceiver::handle_match() {
    Command command = INITIALIZE_COMMAND;
    protocol.recv_match(command);
    queue_match->push(command);
}


ClientReceiver::~ClientReceiver() {}
