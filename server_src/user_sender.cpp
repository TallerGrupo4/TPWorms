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
            // command.msg = command.msg.substr(0, command.msg.find('\0'));
            // parser.parse_sending_command_match(command);
            std::cout << "sending snapshot: " << +snapshot.code << std::endl;
            protocol.send_snapshot(snapshot);

            // if (protocol.send_match(command) == SOCKET_FAILED) {
            //     // Catch error SOCKET_FAILED
            //     throw LibError(errno, "Socket was failed");
            // }
        }
    } catch (const ClosedQueue& err) {
        // It is an expected error
    } catch (const LibError& err) {
        if (protocol.is_connected()) {
            std::cout << "An error was caught in the UserSender: " << err.what() << std::endl;
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
