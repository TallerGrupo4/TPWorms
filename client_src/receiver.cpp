#include "receiver.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


ClientReceiver::ClientReceiver(Socket& skt, std::shared_ptr<Queue<Command>> queue, bool& in_match):
        socket(skt), queue(queue), in_match(in_match), parser(), protocol(socket, parser) {}


void ClientReceiver::run() {
    try {
        while (protocol.is_connected() && !_is_dead) {
            Command command = INITIALIZE_COMMAND;
            protocol.recv_lobby(command);
            if (!in_match && (command.code == CASE_JOIN || command.code == CASE_CREATE))
                in_match = true;
            queue->push(command);
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


ClientReceiver::~ClientReceiver() {}
