#include "receiver.h"

#include <iostream>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


ClientReceiver::ClientReceiver(Socket& skt,
                               std::shared_ptr<Queue<Snapshot>> _queue_match,
                               std::atomic<bool>& _in_match, std::atomic<bool>& _is_dead):
        socket(skt),
        queue_match(_queue_match),
        in_match(_in_match),
        parser(),
        protocol(socket, parser),
        is_dead(_is_dead) {}


void ClientReceiver::run() {
    try {
        while (protocol.is_connected() && !is_dead) {
            Snapshot snapshot = protocol.recv_snapshot();
            queue_match->push(snapshot);
        }
    } catch (const LibError& e) {
        // It is an expected error, it means that the socket has been closed.
        // std::cout << "ClientReceiver has finished because LibError: " << e.what() << std::endl;
    } catch (const ClosedQueue& e) {
        // It is an expected error, it means that the queue has been closed.
        // std::cout << "ClientReceiver has finished because ClosedQueue: " << e.what() <<
        // std::endl;
    } catch (...) {
        std::cerr << "ClientReceiver has finished because of an unknown error" << std::endl;
    }
}


ClientReceiver::~ClientReceiver() {}
