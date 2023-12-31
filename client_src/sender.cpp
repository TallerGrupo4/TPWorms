#include "sender.h"

#include <iostream>
#include <memory>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


ClientSender::ClientSender(Socket& skt, std::shared_ptr<Queue<Command>> _queue_lobby,
                           std::shared_ptr<Queue<std::shared_ptr<Action>>> _queue_match,
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
            std::shared_ptr<Action> action = queue_match->pop();
            protocol.send_action(action);
        }
    } catch (const LibError& e) {
        std::cout << "ClientSender has finished because LibError: " << e.what() << std::endl;
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the queue has been closed.
    } catch (...) {
        std::cerr << "ClientSender has finished because of an unknown error" << std::endl;
    }
}

ClientSender::~ClientSender() {}
