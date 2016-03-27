#include "managerclients.h"

managerClients::managerClients(QObject *parent) : QObject(parent)
{

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
