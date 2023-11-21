#include "user_sender.h"


UserSender::UserSender(Socket& skt, ProtocolServer& protocol):
        socket(skt),
        queue(std::make_shared<Queue<Snapshot>>(QUEUE_MAX_SIZE)),
        parser(),
        protocol(protocol) {}

void UserSender::run() {
    try {
        while (protocol.is_connected()) {
            Snapshot snapshot = queue->pop();
            protocol.send_snapshot(snapshot);
        }
    } catch (const ClosedQueue& err) {
        // It is an expected error
        // std::cout << "The UserSender's queue was closed" << std::endl;
    } catch (const LibError& err) {
        if (protocol.is_connected()) {
            std::cout << "An error was caught in the UserSender: " << err.what() << std::endl;
        } else {
            std::cout << "The UserSender was closed" << std::endl;
        }
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in the "
                     "UserSender"
                  << std::endl;
    }
}

void UserSender::stop() { queue->close(); }

std::shared_ptr<Queue<Snapshot>> UserSender::get_queue() { return queue; }


UserSender::~UserSender() {}
