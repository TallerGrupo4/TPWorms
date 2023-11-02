#include <gtest/gtest.h>
#include <cstdlib>
#include <thread>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../common_src/constants.h"
#include "../common_src/dummy_socket.h"


const char* serverExecutable = "../build/server";
const char* clientExecutable = "../build/client";
const char* serverPort = "8080";
const char* ip = "localhost";

TEST(Protocol, InitializeProtocol) {
    Socket socket_server(serverPort);
    Socket socket_client(ip, serverPort);
    Socket socket_server_accept = socket_server.accept();
    // ParserClient parser = ParserClient();
    // ProtocolClient protocol(socket_client, parser);
    ASSERT_NE(socket_server, socket_client);
}

// TEST(StartingServerAndClient, ServerClient) {
//     // Start the server in the background using a system command
//     std::string startServerCommand = serverExecutable + " " + serverPort;
//     int serverStatus = system(startServerCommand.c_str());

//     // Check if the server started successfully
//     ASSERT_EQ(serverStatus, 32512);

//     // Give the server some time to start (you might need to adjust this)
//     std::this_thread::sleep_for(std::chrono::seconds{2});  // Use C++17 initialization syntax

//     // Start the client to connect to the server
//     std::string startClientCommand = clientExecutable + " localhost " + serverPort;
//     int clientStatus = system(startClientCommand.c_str());

//     // Check if the client ran successfully
//     ASSERT_EQ(clientStatus, 32512);

//     // Implement your test cases for communication between client and server
//     // Send messages and verify responses using appropriate assertions

//     // You can also use popen() or other methods to communicate with server/client
//     // and capture their output or input for testing.
// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
