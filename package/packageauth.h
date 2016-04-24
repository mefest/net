#ifndef PACKAGEAUTH_H
#define PACKAGEAUTH_H

#include "package/package.h"
#include <QObject>
#include <QVersionNumber>


class PackageAuth : public Package
{
    Q_OBJECT
    enum Auth_Type:quint8
    {none=0,Login=1,Passwd=2,IP=4};
public:
    explicit PackageAuth(QObject *parent=0 );

    QString login;
    QString passwd;

friend QDataStream & operator <<(QDataStream& s, const PackageAuth &us);
friend QDataStream & operator <<(QDataStream& s, const PackageAuth *us);
friend QDataStream & operator >>(QDataStream& s,  PackageAuth *us);

private:

// Package interface
public:
void fromStream(QDataStream &stream);
QByteArray serialize();
quint16 getSize();
void dump();
};

#endif // PACKAGEAUTH_H
