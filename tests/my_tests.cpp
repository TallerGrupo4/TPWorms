#include <gtest/gtest.h>
#include <cstdlib>
#include <thread>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../server_src/parser_server.h"
#include "../server_src/protocol_server.h"
#include "../common_src/constants.h"
#include "../common_src/dummy_socket.h"

const char* serverPort = "8080";
const char* ip = "localhost";

std::pair<ProtocolClient, ProtocolServer> createProtocols(Socket& dummy_socket) {
    ParserClient parserClient;
    ParserServer parserServer;
    ProtocolClient protocolClient(dummy_socket, parserClient);
    ProtocolServer protocolServer(dummy_socket, parserServer);
    return std::make_pair(protocolClient, protocolServer);
}


TEST(Protocol, InitializeProtocols) {
    Socket dummy_socket(serverPort);
    auto protocols = createProtocols(dummy_socket);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    ASSERT_EQ(protocolClient, protocolServer);
}

TEST(Socket, sendAndReceive) {
    Socket socket(ip, serverPort);
    std::string msg = "Hello";
    bool was_closed = false;
    socket.sendall(msg.c_str(), msg.length(), &was_closed);
    char buffer[6];
    socket.recvall(buffer, 6, &was_closed);
    ASSERT_EQ(msg, buffer);
}

TEST(Protocol, SendAndReceiveJoin) {
    Socket dummy_socket(serverPort);
    auto protocols = createProtocols(dummy_socket);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_JOIN;
    command_sent.match_id = 10;
    protocolClient.send_create_join(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv(command_received);
    ASSERT_EQ(command_received.code, CASE_JOIN);
    ASSERT_EQ(command_received.match_id, 10);
}


TEST(Protocol, SendAndReceiveWithArguments) {
    Socket dummy_socket(serverPort);
    auto protocols = createProtocols(dummy_socket);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_CHAT;
    std::string msg = "Chating";
    command_sent.msg = msg;
    protocolClient.send(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv(command_received);
    ASSERT_EQ(command_received.code, CASE_CHAT);
    ASSERT_EQ(command_received.msg, msg);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
