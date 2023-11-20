#include <cstdint>
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


// LOBBY

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

TEST(ProtocolHappyCasesLobbyClient, List_matches) {
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

// END LOBBY






// PSEUDO LOBBY

TEST(ProtocolHappyCasesPseudoLobbyClient, Start_match) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_START, 1, "map_name");
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_START);
    ASSERT_EQ(command_received.get_match_id(), 1);
    ASSERT_EQ(command_received.get_map_name(), "map_name");
}

TEST(ProtocolHappyCasesPseudoLobbyClient, Number_of_players_1) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_NUMBER_OF_PLAYERS, 1);
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_NUMBER_OF_PLAYERS);
}

TEST(ProtocolHappyCasesPseudoLobbyServer, Start_match_send_map) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    WormSnapshot worm_snapshot('1', 1, 1, 1, 1, 1, 1, 1, 1);
    PlatformSnapshot platform_snapshot(LargeVertical, 1, 1, PLAT_BIG, PLAT_HEIGHT);
    std::vector<WormSnapshot> worms = {worm_snapshot};
    std::vector<PlatformSnapshot> platforms = {platform_snapshot};
    Snapshot snapshot_to_send(worms, platforms, 1, 1, WORM_WIDTH, WORM_HEIGHT);
    protocol_server.send_snapshot(snapshot_to_send);
    Snapshot snapshot_received = protocol_client.recv_snapshot();
    ASSERT_EQ(snapshot_received.worms.size(), 1);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).max_health, 1);
    ASSERT_EQ(snapshot_received.platforms.size(), 1);
    ASSERT_EQ(snapshot_received.height, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.width, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.worm_width, WORM_WIDTH * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.worm_height, WORM_HEIGHT * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).pos_x, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.platforms.at(0).type, LargeVertical);
    ASSERT_EQ(snapshot_received.platforms.at(0).pos_x, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.platforms.at(0).width, std::round(PLAT_BIG * PIX_PER_METER));
    ASSERT_EQ(snapshot_received.platforms.at(0).height, std::round(PLAT_HEIGHT * PIX_PER_METER));
}

TEST(ProtocolHappyCasesPseudoLobbyServer, Number_of_players_1) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_to_send(CASE_NUMBER_OF_PLAYERS, 1);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_NUMBER_OF_PLAYERS);
}

// END PSEUDO LOBBY




// MATCH

TEST(ProtocolHappyCasesMatch, Send_action_mov_right_and_recv_gameCommand_mov_right) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<ActionMov> action = std::make_shared<ActionMovRight>();
    protocol_client.send_action(action);
    uint8_t worm_id = 1;
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command(worm_id);
    MoveCommand* moveCommand = dynamic_cast<MoveCommand*>(game_command.get());
    ASSERT_NE(moveCommand, nullptr);
    ASSERT_EQ(moveCommand->get_direction(), RIGHT);
}

TEST(ProtocolHappyCasesMatch, Send_and_recv_snapshot) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    WormSnapshot worm_snapshot('1', 1, 1, 1, 1, 1, 1, 1, 1);
    WormSnapshot worm_snapshot2('2', 2, 2, 2, 2, 2, 2, 2, 2);
    std::vector<WormSnapshot> worms = {worm_snapshot, worm_snapshot2};
    Snapshot snapshot_to_send(worms, {});
    protocol_server.send_snapshot(snapshot_to_send);
    Snapshot snapshot_received = protocol_client.recv_snapshot();
    ASSERT_EQ(snapshot_received.worms.size(), 2);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).max_health, 1);
    ASSERT_EQ(snapshot_received.worms.at(1).id, '2');
    ASSERT_EQ(snapshot_received.worms.at(1).max_health, 2);
    ASSERT_EQ(snapshot_received.platforms.size(), 0);
    ASSERT_NE(snapshot_received.height, 10);
}

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
