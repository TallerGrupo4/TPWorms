#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "../client.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(Client& client, QObject *parent = nullptr);

public slots:
    void doWork();

signals:
    void workFinished(const Snapshot& map);

private:
    Client& client;
};

#endif //WORKER_H