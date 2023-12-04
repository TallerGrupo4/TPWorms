#include "worker.h"

Worker::Worker(Client& client, QObject *parent) : QObject(parent), client(client) {}

void Worker::doWork() {
    auto map = client.recv_map();
    emit workFinished(map);
}