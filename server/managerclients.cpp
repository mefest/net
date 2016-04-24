#include "managerclients.h"
#include <QDebug>

managerClients::managerClients(QObject *parent) : QObject(parent)
{
    authManager= new AuthManager(this);
}

void managerClients::add(Client *client)
{
    list[client->getDescriptor()]=client;
}

void managerClients::remove(Client *client)
{
    list.remove(client->getDescriptor());
    del(client);
}
void managerClients::del(Client *client)
{
    client->deleteLater();
}

bool managerClients::authorization(PackageAuth *pkAuth)
{
    if(authManager->authorization(pkAuth)){
        if(isLoginFree(pkAuth->login)){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool managerClients::isLoginFree(QString login)
{
    qDebug()<<login;
    bool result=true;
    for(auto user:list){
        if(user->getLogin()==login){
            result=false;
            return result;
        }
    }
    return result;
}
