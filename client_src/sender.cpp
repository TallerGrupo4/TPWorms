#include "sender.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


ClientSender::ClientSender(Socket& skt, std::shared_ptr<Queue<Command>> _queue_lobby,
                           std::shared_ptr<Queue<Action>> _queue_match,
                           std::atomic<bool>& _in_match, std::atomic<bool>& _is_dead):
        socket(skt),
        queue_lobby(_queue_lobby),
        queue_match(_queue_match),
        in_match(_in_match),
        parser(),
        protocol(socket, parser),
        is_dead(_is_dead) {}


void ClientSender::run() {
    try {
        while (protocol.is_connected() && !is_dead) {
            Action action = queue_match->pop();
            protocol.send_action(action);
            std::cout << "ClientSender has sent an action with code: " << +action.code << std::endl;
            // if (in_match) {
            //     std::cout << "ClientSender is in match" << std::endl;
            //     handle_match();
            // } else {
            //     std::cout << "ClientSender is in lobby" << std::endl;
            //     handle_lobby();
            // }
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

void ClientSender::handle_lobby() {
    try {
        Command command = queue_lobby->pop();
        protocol.send_command(command);
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the lobby queue has been closed.
        std::cout << "The queue_lobby has been closed: " << e.what() << std::endl;
    }
}

void ClientSender::handle_match() {
    std::cout << "ClientSender is handling match" << std::endl;
    Action action = queue_match->pop();
    std::cout << "sending action: " << +action.code << std::endl;
    protocol.send_action(action);
}

ClientSender::~ClientSender() {}
