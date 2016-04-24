#ifndef MANAGERCLIENTS_H
#define MANAGERCLIENTS_H

#include <QObject>
#include <QTcpSocket>
#include "authmanager.h"
#include "client/client.h"
#include "package/packageauth.h"

class managerClients : public QObject
{
    Q_OBJECT
public:
    explicit managerClients(QObject *parent = 0);

    QHash<qintptr,Client*> list;
    void add(Client* client);
    void remove(Client* client);
    void del(Client* client);
    bool authorization(PackageAuth *pkAuth);


private:
    AuthManager *authManager;

    bool isLoginFree(QString login);


signals:

public slots:
};

#endif // MANAGERCLIENTS_H
