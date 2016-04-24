#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include "package/package.h"

class Client : public QObject
{
    Q_OBJECT
public:

    enum Client_State{Closed, SYN, Estabilished};
    explicit Client(QObject *parent = 0);

    QString login;

    bool connectTo(QHostAddress addr, quint16 port);
    bool connectTo(QString addr, quint16 port);
    void send(QByteArray &block);
    void setSocked(QTcpSocket *soked);
    Client_State getState(){ return state; }
    bool isAuth(){ return auth; }
    QString getLogin() { return login; }
signals:

public slots:
    void onSokError(QAbstractSocket::SocketError sError);
    void onConnected();
    void onRead();
    qintptr getDescriptor(){ return descriptor; }
    void sendPackage(Package *package);// send and remove Package;
    void onDisconnect();

private:
    bool auth;
    int compres;
    qintptr descriptor;
    quint16 _blockSize;
    Client_State state;
    QTcpSocket *sok;
    QString passwd;

    bool authorization();
signals:
    void recivPackage(Package*);
    void disconnect();

};

#endif // CLIENT_H
