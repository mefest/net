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
    explicit Client(QObject *parent = 0);


    bool connectTo(QHostAddress addr, quint16 port);
    bool connectTo(QString addr, quint16 port);
    void send(QByteArray &block);

    void setSocked(QTcpSocket *soked);


signals:

public slots:
    void onSokError(QAbstractSocket::SocketError sError);
    void onConnected();
    void onRead();
    qintptr getDescriptor(){ return descriptor; }

private:
    QTcpSocket *sok;
    qintptr descriptor;
    int compres;
    quint16 _blockSize;

signals:
    void recivPackage(Package*);
    void disconnect();
};

#endif // CLIENT_H
