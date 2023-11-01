#include "protocol.h"

// #ifndef TESTING
Protocol::Protocol(Socket& socket, Parser& parser): socket(socket), parser(parser) {}
// #endif
int Protocol::Protocol::recv(Command& command) { return 0; }

int Protocol::Protocol::send(const Command& command) { return 0; }

bool Protocol::is_connected() { return !was_closed; }

Protocol::~Protocol() {}
