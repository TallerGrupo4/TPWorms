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
    Command command_sent(CASE_LIST);
    protocol_client.send_command(command_sent);
    Command command_received = protocol_server.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_LIST);
    ASSERT_EQ(command_received.get_available_matches().size(), 0);
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
    Command command_to_send(CASE_CREATE, 1, map_names, 10);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_CREATE);
    ASSERT_EQ(command_received.get_match_id(), 1);
    ASSERT_EQ(command_received.get_map_names().size(), 3);
    ASSERT_EQ(command_received.get_map_names().at(0), "1");
    ASSERT_NE(command_received.get_map_names().at(1), "3");
    ASSERT_EQ(command_received.get_number_of_players(), 10);
}

TEST(ProtocolHappyCasesLobbyServer, Join) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::vector<std::string> map_names = {"1", "2", "3", "4"};
    Command command_to_send(CASE_JOIN, 10, map_names, 100);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_JOIN);
    ASSERT_EQ(command_received.get_match_id(), 10);
    ASSERT_EQ(command_received.get_map_names().size(), 4);
    ASSERT_EQ(command_received.get_map_names().at(1), "2");
    ASSERT_NE(command_received.get_map_names().at(2), "4");
    ASSERT_EQ(command_received.get_number_of_players(), 100);
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
    ASSERT_EQ(command_received.get_available_matches().size(), 1);
    ASSERT_EQ(command_received.get_available_matches().at(1), "map_name");
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
    ASSERT_EQ(command_received.get_available_matches().size(), 3);
    ASSERT_EQ(command_received.get_available_matches().at(1), "map_name");
    ASSERT_EQ(command_received.get_available_matches().at(3), "map_name3");
    ASSERT_NE(command_received.get_available_matches().at(2), "map_name3");
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
    Command command_sent(CASE_NUMBER_OF_PLAYERS);
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
    WormSnapshot worm_snapshot('1', 1, 1, 1, 1, 1, 1, 1, 1, 1);
    PlatformSnapshot platform_snapshot(LargeVertical, 1, 1, PLAT_BIG, PLAT_HEIGHT);
    std::vector<WormSnapshot> worms = {worm_snapshot};
    std::vector<PlatformSnapshot> platforms = {platform_snapshot};
    Snapshot snapshot_to_send(worms, {}, platforms);
    snapshot_to_send.my_army = {{1, {1}}};
    snapshot_to_send.set_dimensions(1, 1, WORM_WIDTH, WORM_HEIGHT, 1);
    protocol_server.send_snapshot(snapshot_to_send);
    Snapshot snapshot_received = protocol_client.recv_snapshot();
    ASSERT_EQ(snapshot_received.worms.size(), 1);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).max_health, 1);
    ASSERT_EQ(snapshot_received.platforms.size(), 1);
    ASSERT_EQ(snapshot_received.map_dimensions.height, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.map_dimensions.width, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.map_dimensions.worm_width, std::round(WORM_WIDTH * PIX_PER_METER));
    ASSERT_EQ(snapshot_received.map_dimensions.worm_height, std::round(WORM_HEIGHT * PIX_PER_METER));
    ASSERT_EQ(snapshot_received.map_dimensions.amount_of_worms, 1);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).pos_x, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.platforms.at(0).type, LargeVertical);
    ASSERT_EQ(snapshot_received.platforms.at(0).pos_x, 1 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.platforms.at(0).width, std::round(PLAT_BIG * PIX_PER_METER));
    ASSERT_EQ(snapshot_received.platforms.at(0).height, std::round(PLAT_HEIGHT * PIX_PER_METER));
    ASSERT_EQ(snapshot_received.worms.at(0).team_id, 1);
    ASSERT_EQ(snapshot_received.my_army.at(1).at(0), 1); 
}

TEST(ProtocolHappyCasesPseudoLobbyServer, Number_of_players_1) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_to_send(CASE_NUMBER_OF_PLAYERS, 1, {""}, 10);
    protocol_server.send_command(command_to_send);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_NUMBER_OF_PLAYERS);
    ASSERT_EQ(command_received.get_number_of_players(), 10);
}

// END PSEUDO LOBBY




// MATCH



// SEND ACTIONS AND RECV GAME COMMANDS

TEST(ProtocolHappyCasesMatch, Send_action_mov_right_and_recv_gameCommand_mov_right) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<ActionMov> action = std::make_shared<ActionMovRight>();
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    MoveCommand* moveCommand = dynamic_cast<MoveCommand*>(game_command.get());
    ASSERT_NE(moveCommand, nullptr);
    ASSERT_EQ(moveCommand->get_direction(), RIGHT);
}


TEST(ProtocolHappyCasesMatch, Send_action_mov_left_and_recv_gameCommand_mov_left) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client,
                                     parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<ActionMov> action = std::make_shared<ActionMovLeft>();
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    MoveCommand* moveCommand = dynamic_cast<MoveCommand*>(game_command.get());
    ASSERT_NE(moveCommand, nullptr);
    ASSERT_EQ(moveCommand->get_direction(), LEFT);
}


TEST(ProtocolHappyCasesMatch, Send_action_jump_forward_and_recv_gameCommand_jump_forward) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<ActionMov> action = std::make_shared<ActionJump>();
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    JumpCommand* jumpCommand = dynamic_cast<JumpCommand*>(game_command.get());
    ASSERT_NE(jumpCommand, nullptr);
    ASSERT_EQ(jumpCommand->get_direction(), FORWARD);
}

TEST(ProtocolHappyCasesMatch, Send_action_jump_backward_and_recv_gameCommand_jump_backward) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket,
                                     parser_client,
                                     parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<ActionMov> action = std::make_shared<ActionBackflip>();
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    JumpCommand* jumpCommand = dynamic_cast<JumpCommand*>(game_command.get());
    ASSERT_NE(jumpCommand, nullptr);
    ASSERT_EQ(jumpCommand->get_direction(), BACKWARD);
}

TEST(ProtocolHappyCasesMatch, Send_action_aim_and_recv_gameCommand_aim) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket,
                                     parser_client,
                                     parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<Action> action = std::make_shared<ActionAim>(1, 2, 3);
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    AimCommand* aimCommand = dynamic_cast<AimCommand*>(game_command.get());
    ASSERT_NE(aimCommand, nullptr);
    ASSERT_EQ(aimCommand->get_worm_id(), 3);
    ASSERT_EQ(aimCommand->get_look_direction_x(), 1);
    ASSERT_EQ(aimCommand->get_look_direction_y(), 2);
}

TEST(ProtocolHappyCasesMatch, Send_action_shoot_and_recv_gameCommand_shoot) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket,
                                     parser_client,
                                     parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<Action> action = std::make_shared<ActionShooting>(1, 2);
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    UseToolCommand* useToolCommand = dynamic_cast<UseToolCommand*>(game_command.get());
    ASSERT_NE(useToolCommand, nullptr);
    ASSERT_EQ(useToolCommand->get_worm_id(), 2);
    ASSERT_EQ(useToolCommand->get_potency(), 1);
    ASSERT_EQ(useToolCommand->get_pos_x(), 0); // This values are hardcoded in the ProtocoServer
    ASSERT_EQ(useToolCommand->get_pos_y(), 0); // This values are hardcoded in the ProtocoServer
}

TEST(ProtocolHappyCasesMatch, Send_action_change_tool_and_recv_gameCommand_change_tool) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket,
                                     parser_client,
                                     parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    std::shared_ptr<Action> action = std::make_shared<ActionChangeWeapon>(1, 2);
    protocol_client.send_action(action);
    std::shared_ptr<GameCommand> game_command = protocol_server.recv_game_command();
    ChangeToolCommand* changeToolCommand = dynamic_cast<ChangeToolCommand*>(game_command.get());
    ASSERT_NE(changeToolCommand, nullptr);
    ASSERT_EQ(changeToolCommand->get_direction(), 1);
    ASSERT_EQ(changeToolCommand->get_worm_id(), 2);
}


// SEND AND RECV SNAPSHOT

TEST(ProtocolHappyCasesMatch, Send_and_recv_snapshot) {
    // SEPARATE THIS TEST INTO MULTIPLE TESTS
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    WormSnapshot worm_snapshot('1', 1, 1, 1, 1, 1, 1, 1, 1, 1);
    WormSnapshot worm_snapshot2('2', 2, 2, 2, 2, 2, 2, 2, 2, 2);
    std::vector<WormSnapshot> worms = {worm_snapshot, worm_snapshot2};
    ProjectileSnapshot projectile_snapshot(EXPLOSIVE, 2, 3, 4 * RADTODEG);
    std::vector<ProjectileSnapshot> projectiles = {projectile_snapshot};
    Snapshot snapshot_to_send(worms, projectiles, {});
    snapshot_to_send.set_turn_time_and_worm_turn(12, 21);
    snapshot_to_send.set_dimensions(100, 100, 100, 100);
    protocol_server.send_snapshot(snapshot_to_send);
    Snapshot snapshot_received = protocol_client.recv_snapshot();
    ASSERT_EQ(snapshot_received.worms.size(), 2);
    ASSERT_EQ(snapshot_received.worms.at(0).id, '1');
    ASSERT_EQ(snapshot_received.worms.at(0).max_health, 1);
    ASSERT_EQ(snapshot_received.worms.at(1).id, '2');
    ASSERT_EQ(snapshot_received.worms.at(1).max_health, 2);
    ASSERT_EQ(snapshot_received.worms.at(0).team_id, 1);
    ASSERT_EQ(snapshot_received.worms.at(1).team_id, 2);
    ASSERT_EQ(snapshot_received.platforms.size(), 0);
    ASSERT_EQ(snapshot_received.map_dimensions.width, 100 * PIX_PER_METER);
    ASSERT_NE(snapshot_received.map_dimensions.height, 10 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.map_dimensions.worm_width, 100 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.map_dimensions.worm_height, 100 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.turn_time_and_worm_turn.turn_time, 12);
    ASSERT_NE(snapshot_received.turn_time_and_worm_turn.worm_turn, 12);
    ASSERT_EQ(snapshot_received.projectiles.size(), 1);
    ASSERT_EQ(snapshot_received.projectiles.at(0).type, EXPLOSIVE);
    ASSERT_EQ(snapshot_received.projectiles.at(0).pos_x, 2 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.projectiles.at(0).pos_y, 3 * PIX_PER_METER);
    ASSERT_EQ(snapshot_received.projectiles.at(0).angle, std::round(4 * RADTODEG));
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

TEST(ProtocolSadCasesLobby, FullMatch) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_MATCH_FULL, 1);
    protocol_server.send_command(command_sent);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_MATCH_FULL);
    ASSERT_EQ(command_received.get_match_id(), 1);
}

TEST(ProtocolSadCases, MatchNotFound) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_MATCH_NOT_FOUND, 1);
    protocol_server.send_command(command_sent);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_MATCH_NOT_FOUND);
    ASSERT_EQ(command_received.get_match_id(), 1);
}

TEST(ProtocolSadCases, MatchAlreadyExists) {
    Socket dummy_socket(serverPort);
    ParserClient parser_client;
    ParserServer parser_server;
    auto protocols = createProtocols(dummy_socket, parser_client, parser_server);
    ProtocolClient protocol_client = protocols.first;
    ProtocolServer protocol_server = protocols.second;
    Command command_sent(CASE_MATCH_ALREADY_EXISTS, 1);
    protocol_server.send_command(command_sent);
    Command command_received = protocol_client.recv_command();
    ASSERT_EQ(command_received.get_code(), CASE_MATCH_ALREADY_EXISTS);
    ASSERT_EQ(command_received.get_match_id(), 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
