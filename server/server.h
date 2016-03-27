#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "managerclients.h"
#include "package/package.h"

class Server : public QTcpServer
{
Q_OBJECT
public:
    enum server_status{stop=0,run};
    explicit Server(QObject *parent);
    bool start(QHostAddress addr=QHostAddress::Any, quint16 port=0);
    server_status getStatus(){return status;}

    managerClients *mClients;

protected:
    void incomingConnection(qintptr handle);

private:
    server_status status;



public slots:
    void onRecivPackage(Package* package);
    void onDisconnect();


};

#endif // SERVER_H
