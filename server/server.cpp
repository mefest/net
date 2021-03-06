#include "server.h"
#include "package/package.h"
#include "package/packagecommand.h"
#include "package/packagemessage.h"
#include "client/client.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{
    status=Server::stop;
    mClients= new managerClients(this);

}

bool Server::start(QHostAddress addr, quint16 port)
{
    if(this->listen(addr, port)){
        status=Server::run;
        return true;
    }else{
        return false;
    }
}

bool Server::start(QString addr, quint16 port)
{
    return this->start(QHostAddress(addr),port);
}

void Server::incomingConnection(qintptr handle)
{
    //передаем дескрпитор сокета, указатель на сервер (для вызова его методов), и стандартный параметр - parent
//        MyClient *client = new MyClient(handle, this, this);
        QTcpSocket *sok= new QTcpSocket(this);

        sok->setSocketDescriptor(handle);

        Client *client = new Client(this);
        connect(client, SIGNAL(recivPackage(Package*)),this,SLOT(onRecivPackage(Package*)));
        connect(client,SIGNAL(disconnect()),this,SLOT(onDisconnect()));
        client->setSocked(sok);
//        mClients->add(client);
        qDebug()<<"new connect on server";
}

void Server::onRecivPackage(Package *package)
{
    Client *client=qobject_cast<Client*>(QObject::sender());
    if(package->getType()==Package::Auth && ( !client->isAuth() ) ){
        PackageAuth *auth=qobject_cast<PackageAuth*>(package);
        if( mClients->authorization( auth) ){
            mClients->add(client);
            client->login=auth->login;
            qDebug()<<"auth coml";
        }else{
            qDebug()<<"Ошибка авторизации";
        }
    }else{
        PackageMessage *pkMes=qobject_cast<PackageMessage*>(package);
//        qDebug()<<"сервер получил пакет типа "<<pkMes->getMessage();
    }

    emit recivPackage(package);
}

void Server::onDisconnect()
{
    Client *client=qobject_cast<Client*>(QObject::sender());
    mClients->remove(client);
    qDebug()<<"client disc";

}


