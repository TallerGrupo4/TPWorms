#include "server_server_client_sender.h"

ServerClientSender::ServerClientSender(Socket& skt, std::shared_ptr<Queue<Command>> queue,
                                       ProtocolServer& protocol):
        socket(skt), queue(queue), parser(), protocol(protocol) {}

void ServerClientSender::run() {
    try {
        while (protocol.is_connected()) {
            Command command = queue->pop();
            command.msg = command.msg.substr(0, command.msg.find('\0'));
            parser.parse_sending_command(command);
            std::cout << "sending command: " << +command.code << std::endl;
            if (protocol.send(command) == SOCKET_FAILED) {
                // Catch error SOCKET_FAILED
                throw LibError(errno, "Socket was failed");
            }
        }
    } catch (const ClosedQueue& err) {
        // It is an expected error
    } catch (const LibError& err) {
        if (protocol.is_connected()) {
            std::cout << "An error was caught in the ServerClientSender: " << err.what()
                      << std::endl;
        }
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in the "
                     "ServerClientSender"
                  << std::endl;
    }
}


ServerClientSender::~ServerClientSender() {}
