#include "client.h"
#include "QAbstractSocket"
#include "package/packagecommand.h"
#include "package/packagemessage.h"

Client::Client(QObject *parent) : QObject(parent)
{
    compres=0;
    sok=nullptr;
    setSocked(new QTcpSocket(this));

}

bool Client::connectTo(QHostAddress addr, quint16 port)
{
    sok->connectToHost(addr, port);
    return true;
}

bool Client::connectTo(QString addr, quint16 port)
{
    sok->connectToHost(addr, port);
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
    connect(sok,SIGNAL(disconnected()),this,SIGNAL(disconnect()));
}

void Client::onSokError(QAbstractSocket::SocketError sError)
{
    qDebug()<<sError;
}

void Client::onConnected()
{
    QTcpSocket *socket= qobject_cast<QTcpSocket*>(QObject::sender());
    descriptor=socket->socketDescriptor();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    PackageMessage *pkMes= new PackageMessage();
    pkMes->setMessage("hi my server");
    out<<pkMes;
    send(block);
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
        int type;
        in>>type;
        qDebug()<<"Тип "<<type<<"\t\t|";
        switch (type) {
        case Package::Unknow:
            return;
            break;
        case Package::Command:
        {
            int com;
            in>>com;
            package= new PackageCommand(_blockSize,com);
            break;
        }
        case Package::Message:
        {
            QString mes;
            in>>mes;
            package= new PackageMessage(_blockSize,mes);
            break;
        }
        default:
            return;
            break;
        }
        qDebug()<<"-----------------------";
    emit recivPackage(package);
    }
}

