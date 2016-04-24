#include "client.h"
#include "QAbstractSocket"
#include "package/packagecommand.h"
#include "package/packagemessage.h"
#include "package/packageauth.h"
#include "package/packagefilehandler.h"

Client::Client(QObject *parent) : QObject(parent), state(Closed)
{
    compres=0;
    sok=nullptr;
    setSocked(new QTcpSocket(this));
    _blockSize=0;
    auth=false;
}

bool Client::connectTo(QHostAddress addr, quint16 port)
{
    sok->connectToHost(addr, port);
    state=Client_State::SYN;
    return true;
}

bool Client::connectTo(QString addr, quint16 port)
{
    sok->connectToHost(addr, port);
    state=Client_State::SYN;
    return true;
}

void Client::send(QByteArray &block)
{
    if(compres){
        sok->write(qCompress(block,compres));
    }else{
        sok->write(block);
    }
}

void Client::setSocked(QTcpSocket *soked)
{
    if(sok!=nullptr){
        sok->deleteLater();
    }
    sok= soked;
    descriptor=sok->socketDescriptor();
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokError(QAbstractSocket::SocketError)));
    connect(sok,SIGNAL(connected()), this, SLOT(onConnected()));
    connect(sok,SIGNAL(readyRead()),this,SLOT(onRead()));
    connect(sok,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
}

void Client::onSokError(QAbstractSocket::SocketError sError)
{
    qDebug()<<sError;
}

void Client::onConnected()
{
    QTcpSocket *socket= qobject_cast<QTcpSocket*>(QObject::sender());
    descriptor=socket->socketDescriptor();
    state=Client_State::Estabilished;
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
}

void Client::onRead()
{
    qDebug()<<"onRead";
    QDataStream in(sok);
    Package *package;
    while(!in.atEnd())
    {
        if(_blockSize==0){
            if (sok->bytesAvailable() < (int)sizeof(quint16))
                return;
            in >> _blockSize;
            qDebug()<<"Полученно--------------";
            qDebug()<<"размер"<<_blockSize<<"\t\t|";
        }
        if (sok->bytesAvailable() < _blockSize)
            return;
        else
            _blockSize = 0;
        quint16 type;
        in>>type;
        qDebug()<<"Тип "<<type<<"\t\t|";
        switch (type) {
        case Package::Unknow:
            return;
            break;
        case Package::Command:
        {
            package= new PackageCommand();
            break;
        }
        case Package::Message:
        {
            package= new PackageMessage();
            break;
        }
        case Package::Auth:
        {
            package= new PackageAuth();
            break;
        }
        case Package::FileHandler:
        {
            package= new PackageFileHandler();
            break;
        }
        default:
            qDebug()<<"Необъявленный пакет";
            return;
            break;
        }
        package->user=sok->socketDescriptor();
        qDebug()<<"from\t"<<package->user<<"\t|";
        package->fromStream(in);
        package->dump();
        qDebug()<<"-----------------------";
    emit recivPackage(package);
    }
}

void Client::sendPackage(Package *package)
{
    QByteArray block=package->serialize();
    send(block);
}

void Client::onDisconnect()
{
    state=Client_State::Closed;
    emit disconnect();
}

bool Client::authorization()
{

}

