#ifndef PACKAGECOMMAND_H
#define PACKAGECOMMAND_H
#include <QObject>
#include "package/package.h"

class PackageCommand : public  Package
{
    Q_OBJECT
public:
    explicit PackageCommand(QObject *parent=0 );
    explicit PackageCommand(quint16 _size, quint16 _com, QObject *parent=0);

    quint16 command;


friend QDataStream & operator <<(QDataStream& s, const PackageCommand &us);
friend QDataStream & operator <<(QDataStream& s, const PackageCommand *us);

friend QDataStream & operator >>(QDataStream& s,  PackageCommand *us);


// Package interface
public:
QByteArray serialize();
quint16 getSize();
void fromStream(QDataStream &stream);
void dump();
};


#endif // PACKAGECOMMAND_H
