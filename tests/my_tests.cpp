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
                                                          ParserClient& parser_client,
                                                          ParserServer& parser_server) {
    ProtocolClient protocol_client(dummy_socket, parser_client);
    ProtocolServer protocol_server(dummy_socket, parser_server);
    return std::make_pair(protocol_client, protocol_server);
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

TEST(ProtocolHappyCasesLobbyClient, Join) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_JOIN, 10);
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_JOIN);
    ASSERT_EQ(command_received.get_match_id(), 10);
    ASSERT_NE(command_received.get_code(), CASE_CREATE);
    ASSERT_NE(command_received.get_match_id(), 1);
}

TEST(ProtocolHappyCasesLobbyClient, Create) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_CREATE, 1);
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_CREATE);
    ASSERT_EQ(command_received.get_match_id(), 1);
    ASSERT_NE(command_received.get_code(), CASE_JOIN);
    ASSERT_NE(command_received.get_match_id(), 10);
}

TEST(ProtocolHappyCasesLobbyClient, ListMatches) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_LIST, DEFAULT);
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_LIST);
    ASSERT_EQ(command_received.get_matches_availables().size(), 0);
    ASSERT_NE(command_received.get_code(), CASE_JOIN);
}

TEST(ProtocolHappyCasesLobbyServer, Create) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::vector<std::string> map_names = {"1", "2", "3"};
    Command command_to_send(CASE_CREATE, 1, map_names, 10, 0);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_CREATE);
    ASSERT_EQ(command_received.get_match_id(), 1);
    ASSERT_EQ(command_received.get_map_names().size(), 3);
    ASSERT_EQ(command_received.get_map_names().at(0), "1");
    ASSERT_NE(command_received.get_map_names().at(1), "3");
    ASSERT_EQ(command_received.get_number_of_players(), 10);
    ASSERT_EQ(command_received.get_worm_id(), 0);
}

TEST(ProtocolHappyCasesLobbyServer, Join) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::vector<std::string> map_names = {"1", "2", "3", "4"};
    Command command_to_send(CASE_JOIN, 10, map_names, 100, 1);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_JOIN);
    ASSERT_EQ(command_received.get_match_id(), 10);
    ASSERT_EQ(command_received.get_map_names().size(), 4);
    ASSERT_EQ(command_received.get_map_names().at(1), "2");
    ASSERT_NE(command_received.get_map_names().at(2), "4");
    ASSERT_EQ(command_received.get_number_of_players(), 100);
    ASSERT_EQ(command_received.get_worm_id(), 1);
}

TEST(ProtocolHappyCasesLobbyServer, List_1_Match) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::map<uint, std::string> matches_availables = {{1, "map_name"}};
    Command command_send_list(CASE_LIST, matches_availables);
    protocol_server.send_command(command_send_list);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_LIST);
    ASSERT_EQ(command_received.get_matches_availables().size(), 1);
    ASSERT_EQ(command_received.get_matches_availables().at(1), "map_name");
}

TEST(ProtocolHappyCasesLobbyServer, List_more_than_1_Match) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::map<uint, std::string> matches_availables = {{1, "map_name"}, {2, "map_name2"}, {3, "map_name3"}};
    Command command_send_list(CASE_LIST, matches_availables);
    protocol_server.send_command(command_send_list);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_LIST);
    ASSERT_EQ(command_received.get_matches_availables().size(), 3);
    ASSERT_EQ(command_received.get_matches_availables().at(1), "map_name");
    ASSERT_EQ(command_received.get_matches_availables().at(3), "map_name3");
    ASSERT_NE(command_received.get_matches_availables().at(2), "map_name3");
}


// TEST(ProtocolHappyCasesPseudoLobby, StartMatch) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     Command command_sent(CASE_START, 1, "map_name");
//     protocol_client.send_command(command_sent);
//     Command command_received = protocol_server.recv_command();
//     ASSERT_EQ(command_received.get_code(), CASE_START);
//     ASSERT_EQ(command_received.get_match_id(), 1);
//     ASSERT_EQ(command_received.get_map_name(), "map_name");
// }

// TEST(ProtocolHappyCasesMatch, MoveWorm) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     std::shared_ptr<ActionMov> action = std::make_shared<ActionMov>(1, 10);
//     protocol_client.send_action(action);
//     std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
//     ASSERT_EQ(game_command->is_start, false);
//     ASSERT_EQ(game_command->id_worm, 1);
//     // Check if game_command is an instance of MoveCommand
//     MoveCommand* moveCommand = dynamic_cast<MoveCommand*>(game_command.get());
//     ASSERT_NE(moveCommand, nullptr);
    
// }

// TEST(ProtocolHappyCases, ExitServer) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     // Exit not implemented yet
// }

// ----------------------- SAD CASES -----------------------

// Not handling sad cases yet

// TEST(ProtocolSadCases, FullMatch) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_FULL;
//     command_sent.match_id = 1;
//     protocol_server.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocol_client.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_FULL);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_ALREADY_EXISTS);
//     ASSERT_NE(command_received.match_id, 10);
// }

// TEST(ProtocolSadCases, MatchNotFound) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_NOT_FOUND;
//     command_sent.match_id = 1;
//     protocol_server.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocol_client.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_NOT_FOUND);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_FULL);
//     ASSERT_NE(command_received.match_id, 10);
// }

// TEST(ProtocolSadCases, MatchAlreadyExists) {
//     Socket dummy_socket(serverPort);
//     ParserClient parser_client;
//     ParserServer parser_server;
//     auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
//     ProtocolClient protocol_client = protocols.first;
//     ProtocolServer protocol_server = protocols.second;
//     Command command_sent = INITIALIZE_COMMAND;
//     command_sent.code = CASE_MATCH_ALREADY_EXISTS;
//     command_sent.match_id = 1;
//     protocol_server.send_lobby(command_sent);
//     Command command_received = INITIALIZE_COMMAND;
//     protocol_client.recv_lobby(command_received);
//     ASSERT_EQ(command_received.code, CASE_MATCH_ALREADY_EXISTS);
//     ASSERT_EQ(command_received.match_id, 1);
//     ASSERT_NE(command_received.code, CASE_MATCH_NOT_FOUND);
//     ASSERT_NE(command_received.match_id, 10);
// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
