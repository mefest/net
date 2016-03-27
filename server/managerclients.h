#ifndef MANAGERCLIENTS_H
#define MANAGERCLIENTS_H

#include <QObject>
#include <QTcpSocket>
#include "client/client.h"

class managerClients : public QObject
{
    Q_OBJECT
public:
    explicit managerClients(QObject *parent = 0);

    QHash<qintptr,Client*> list;
    void add(Client* client);
    void remove(Client* client);
    void del(Client* client);

private:


signals:

public slots:
};

#endif // MANAGERCLIENTS_H
