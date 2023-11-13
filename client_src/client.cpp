#include "client.h"

#include <iostream>

#include <sys/socket.h>

#include "../common_src/custom_errors.h"
#include "../common_src/liberror.h"


Client::Client(const char* hostname, const char* servername):
        socket(hostname, servername),
        queue_sender_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_sender_match(std::make_shared<Queue<Action>>(QUEUE_MAX_SIZE)),
        queue_receiver_lobby(std::make_shared<Queue<Command>>(QUEUE_MAX_SIZE)),
        queue_receiver_match(std::make_shared<Queue<Snapshot>>(QUEUE_MAX_SIZE)),
        client_sender(std::make_unique<ClientSender>(socket, queue_sender_lobby, queue_sender_match,
                                                     in_match, is_dead)),
        client_receiver(std::make_unique<ClientReceiver>(socket, queue_receiver_lobby,
                                                         queue_receiver_match, in_match, is_dead)),
        parser(), protocol(socket, parser) {
    }

void Client::start() {
    client_sender->start();
    client_receiver->start();
}

void Client::stop() {
    if (!in_match) {
        queue_sender_lobby->close();
    }
    queue_sender_match->close();
    queue_receiver_lobby->close();
    queue_receiver_match->close();
    socket.shutdown(SHUT_RDWR);
    client_sender->join();
    client_receiver->join();
}

Command Client::recv_lobby_command() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    Command command = INITIALIZE_COMMAND;
    protocol.recv_command(command);
    return command;
}

Snapshot Client::recv_snapshot() {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    Snapshot snapshot;
    queue_receiver_match->try_pop(snapshot);
    return snapshot;
}

void Client::send_lobby_command(Command command) {
    if (!protocol.is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    // queue_sender_lobby->push(command);
    protocol.send_command(command);
}

void Client::send_action(Action action) {
    if (!is_connected()) {
        // throw LibError(errno, "Client is not connected");
        // throw LostConnection("Client is not connected");
    }
    queue_sender_match->try_push(action);
}

void Client::exit() {
    is_dead = true;
    stop();
}


bool Client::is_connected() {
    // return protocol.is_connected() && !is_dead;
    return client_sender->is_connected() && client_receiver->is_connected() && !is_dead;
}

Client::~Client() {}