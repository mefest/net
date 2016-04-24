#include "authmanager.h"

AuthManager::AuthManager(QObject *parent) : QObject(parent)
{

}

bool AuthManager::authorization(PackageAuth *pkAuth)
{
    pkAuth->deleteLater();
    return true;
}
