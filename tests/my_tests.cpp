#include <cstdlib>
#include <thread>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../common_src/constants.h"
#include "../common_src/dummy_socket.h"
#include "../server_src/parser_server.h"
#include "../server_src/protocol_server.h"

const char* serverPort = "8080";
const char* ip = "localhost";

std::pair<ProtocolClient, ProtocolServer> createProtocols(Socket& dummy_socket,
                                                          ParserClient& parserClient,
                                                          ParserServer& parserServer) {
    ProtocolClient protocolClient(dummy_socket, parserClient);
    ProtocolServer protocolServer(dummy_socket, parserServer);
    return std::make_pair(protocolClient, protocolServer);
}


TEST(Socket, SocketTest) {
    Socket socket(ip, serverPort);
    std::string msg = "Hello";
    bool was_closed = false;
    socket.sendall(msg.c_str(), msg.length(), &was_closed);
    char buffer[5];
    socket.recvall(buffer, 5, &was_closed);
    ASSERT_EQ(msg, buffer);
}

TEST(ProtocolInitialization, InitializeProtocols) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    ASSERT_EQ(protocolClient, protocolServer);
}

// ----------------------- HAPPY CASES -----------------------

TEST(ProtocolHappyCases, Join) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_JOIN;
    command_sent.match_id = 10;
    protocolClient.send_lobby(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv_lobby(command_received);
    ASSERT_EQ(command_received.code, CASE_JOIN);
    ASSERT_EQ(command_received.match_id, 10);
    ASSERT_NE(command_received.code, CASE_CREATE);
    ASSERT_NE(command_received.match_id, 1);
}

TEST(ProtocolHappyCases, Create) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_CREATE;
    command_sent.match_id = 1;
    protocolClient.send_lobby(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv_lobby(command_received);
    ASSERT_EQ(command_received.code, CASE_CREATE);
    ASSERT_EQ(command_received.match_id, 1);
    ASSERT_NE(command_received.code, CASE_JOIN);
    ASSERT_NE(command_received.match_id, 10);
}


TEST(ProtocolHappyCases, Chat) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_CHAT;
    std::string msg = "Chating";
    command_sent.msg = msg;
    protocolClient.send_match(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolServer.recv_match(command_received);
    ASSERT_EQ(command_received.code, CASE_CHAT);
    ASSERT_EQ(command_received.msg, msg);
    ASSERT_NE(command_received.code, CASE_EXIT_SERVER);
    ASSERT_NE(command_received.msg, "Not Chating");
}

TEST(ProtocolHappyCases, ExitServer) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_EXIT_SERVER;
    protocolServer.send_match(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolClient.recv_match(command_received);
    ASSERT_EQ(command_received.code, CASE_EXIT_SERVER);
    ASSERT_NE(command_received.code, CASE_CHAT);
}

// ----------------------- SAD CASES -----------------------

TEST(ProtocolSadCases, FullMatch) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_MATCH_FULL;
    command_sent.match_id = 1;
    protocolServer.send_lobby(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolClient.recv_lobby(command_received);
    ASSERT_EQ(command_received.code, CASE_MATCH_FULL);
    ASSERT_EQ(command_received.match_id, 1);
    ASSERT_NE(command_received.code, CASE_MATCH_ALREADY_EXISTS);
    ASSERT_NE(command_received.match_id, 10);
}

TEST(ProtocolSadCases, MatchNotFound) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_MATCH_NOT_FOUND;
    command_sent.match_id = 1;
    protocolServer.send_lobby(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolClient.recv_lobby(command_received);
    ASSERT_EQ(command_received.code, CASE_MATCH_NOT_FOUND);
    ASSERT_EQ(command_received.match_id, 1);
    ASSERT_NE(command_received.code, CASE_MATCH_FULL);
    ASSERT_NE(command_received.match_id, 10);
}

TEST(ProtocolSadCases, MatchAlreadyExists) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent = INITIALIZE_COMMAND;
    command_sent.code = CASE_MATCH_ALREADY_EXISTS;
    command_sent.match_id = 1;
    protocolServer.send_lobby(command_sent);
    Command command_received = INITIALIZE_COMMAND;
    protocolClient.recv_lobby(command_received);
    ASSERT_EQ(command_received.code, CASE_MATCH_ALREADY_EXISTS);
    ASSERT_EQ(command_received.match_id, 1);
    ASSERT_NE(command_received.code, CASE_MATCH_NOT_FOUND);
    ASSERT_NE(command_received.match_id, 10);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
