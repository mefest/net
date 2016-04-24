#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include "package/packageauth.h"

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = 0);
    bool authorization(PackageAuth *pkAuth);



signals:

public slots:
};

#endif // AUTHMANAGER_H
