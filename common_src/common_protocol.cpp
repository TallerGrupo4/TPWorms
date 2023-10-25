#include "common_protocol.h"

Protocol::Protocol(Socket& socket, Parser& parser): socket(socket), parser(parser) {}

int Protocol::Protocol::recv(Command& command) { return 0; }

int Protocol::Protocol::send(const Command& command) { return 0; }

bool Protocol::is_connected() { return !was_closed; }

Protocol::~Protocol() {}
