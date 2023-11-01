#include <gtest/gtest.h>

#include "../client_src/parser_client.h"
#include "../client_src/protocol_client.h"
#include "../common_src/constants.h"
#include "./dummy_socket.h"

namespace {
int getNumber() { return 1; }
}  // namespace

TEST(TestTopic, GetNumber) { EXPECT_EQ(getNumber(), 1); }

TEST(Protocol, BasiscTestSendData) {
    // DummySocket socket("localhost", "8080");
    // ParserClient parser;
    // ProtocolClient protocol(socket, parser);
    // Command command = INITIALIZE_COMMAND;
    // EXPECT_EQ(protocol.send(command), 1);
    EXPECT_EQ(getNumber(), 2);
}
