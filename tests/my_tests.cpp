#include <gtest/gtest.h>
#include <cstdlib>
#include <thread>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../server_src/parser_server.h"
#include "../server_src/protocol_server.h"
#include "../common_src/constants.h"
#include "../common_src/dummy_socket.h"

std::pair<ProtocolClient, ProtocolServer> createProtocols() {
    const char* serverPort = "8080";
    const char* ip = "localhost";

    Socket socket_server(serverPort);
    Socket socket_client(ip, serverPort);
    Socket socket_server_accept = socket_server.accept();

    ParserClient parserClient;
    ParserServer parserServer;

    ProtocolClient protocolClient(socket_client, parserClient);
    ProtocolServer protocolServer(socket_server_accept, parserServer);

    return std::make_pair(protocolClient, protocolServer);
}


TEST(Protocol, InitializeProtocols) {
    auto protocols = createProtocols();
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    ASSERT_NE(protocolClient, protocolServer);
}

TEST(Protocol, SendAndReceive) {
    auto protocols = createProtocols();
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    protocolClient.send(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv(command_received);
    ASSERT_EQ(command_received.code, DEFAULT);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
