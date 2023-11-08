#include "protocol.h"

Protocol::Protocol(Socket& socket, Parser& parser): socket(socket), parser(parser) {}

int Protocol::Protocol::recv_command(Command& command) { return 0; }
int Protocol::Protocol::send_command(Command& command) { return 0; }

int Protocol::Protocol::recv_snapshot(Snapshot& snapshot) { return 0; }
int Protocol::Protocol::send_snapshot(Snapshot& snapshot) { return 0; }
int Protocol::Protocol::recv_game_command(GameCommand& game_command) { return 0; }
int Protocol::Protocol::send_action(Action& game_command) { return 0; }

bool Protocol::is_connected() { return !was_closed; }

Protocol::~Protocol() {}
