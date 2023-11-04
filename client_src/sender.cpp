#include "sender.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"
#include "../common_src/constants.h"


ClientSender::ClientSender(Socket& skt, std::shared_ptr<Queue<Command>> queue, bool& in_match):
        socket(skt), queue(queue), in_match(in_match), parser(), protocol(socket, parser) {}


void ClientSender::run() {
    try {
        while (protocol.is_connected() && !_is_dead) {
            Command command = queue->pop();
            if (!in_match) {
                handle_command_not_in_match(command);
            } else {
                handle_command_in_match(command);
            }
        }
    } catch (const LibError& e) {
        std::cout << "ClientSender has finished because LibError: " << e.what() << std::endl;
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the queue has been closed.
        // std::cout << "ClientSender has finished because ClosedQueue: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ClientSender has finished because of an unknown error" << std::endl;
    }
}

void ClientSender::handle_command_not_in_match(Command& command) {
    protocol.send_lobby(command);
}

void ClientSender::handle_command_in_match(const Command& command) {
    switch (command.code) {
        case CASE_CHAT: {
            // TODO: CATCH ERROR SOCKET_FAILED
            protocol.send_match(command);
            break;
        }
        default:
            // TODO: throw a custom error, it should never reach this point.
            break;
    }
}

ClientSender::~ClientSender() {}
