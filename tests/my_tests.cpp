#include <cstdlib>
#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../server_src/parser_server.h"
#include "../server_src/protocol_server.h"
#include "../common_src/dummy_socket.h"
#include "../common_src/snapshot.h"
#include "../server_src/game_src/game_command.h"
#include "../client_src/action.h"

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

// ----------------------- HAPPY CASES -----------------------

TEST(ProtocolHappyCases, Join) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent(CASE_JOIN, 10);
    protocolClient.send_command(command_sent);
    Command command_received = protocolServer.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_JOIN);
    ASSERT_EQ(command_received.get_match_id(), 10);
    ASSERT_NE(command_received.get_code(), CASE_CREATE);
    ASSERT_NE(command_received.get_match_id(), 1);
}

TEST(ProtocolHappyCases, Create) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    Command command_sent(CASE_CREATE, 1);
    protocolClient.send_command(command_sent);
    Command command_received = protocolServer.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_CREATE);
    ASSERT_EQ(command_received.get_match_id(), 1);
    ASSERT_NE(command_received.get_code(), CASE_JOIN);
    ASSERT_NE(command_received.get_match_id(), 10);
}


TEST(ProtocolHappyCases, StartMatch) {
    Socket dummy_socket(serverPort);
    ParserClient parserClient;
    ParserServer parserServer;
    auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
    ProtocolClient protocolClient = protocols.first;
    ProtocolServer protocolServer = protocols.second;
    std::shared_ptr<ActionStart> action = std::make_shared<ActionStart>();
    protocolClient.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocolServer.recv_game_command();
    ASSERT_EQ(game_command->is_start, true);
}

// TEST(ProtocolHappyCases, ExitServer) {
//     Socket dummy_socket(serverPort);
//     ParserClient parserClient;
//     ParserServer parserServer;
//     auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
//     ProtocolClient protocolClient = protocols.first;
//     ProtocolServer protocolServer = protocols.second;
//     // Exit not implemented yet
// }

// ----------------------- SAD CASES -----------------------

// Not handling sad cases yet

// TEST(ProtocolSadCases, FullMatch) {
//     Socket dummy_socket(serverPort);
//     ParserClient parserClient;
//     ParserServer parserServer;
//     auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
//     ProtocolClient protocolClient = protocols.first;
//     ProtocolServer protocolServer = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_FULL;
//     command_sent.match_id = 1;
//     protocolServer.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocolClient.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_FULL);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_ALREADY_EXISTS);
//     ASSERT_NE(command_received.match_id, 10);
// }

// TEST(ProtocolSadCases, MatchNotFound) {
//     Socket dummy_socket(serverPort);
//     ParserClient parserClient;
//     ParserServer parserServer;
//     auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
//     ProtocolClient protocolClient = protocols.first;
//     ProtocolServer protocolServer = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_NOT_FOUND;
//     command_sent.match_id = 1;
//     protocolServer.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocolClient.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_NOT_FOUND);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_FULL);
//     ASSERT_NE(command_received.match_id, 10);
// }

// TEST(ProtocolSadCases, MatchAlreadyExists) {
//     Socket dummy_socket(serverPort);
//     ParserClient parserClient;
//     ParserServer parserServer;
//     auto protocols = createProtocols(dummy_socket, parserClient, parserServer);
//     ProtocolClient protocolClient = protocols.first;
//     ProtocolServer protocolServer = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_ALREADY_EXISTS;
//     command_sent.match_id = 1;
//     protocolServer.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocolClient.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_ALREADY_EXISTS);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_NOT_FOUND);
//     ASSERT_NE(command_received.match_id, 10);
// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
