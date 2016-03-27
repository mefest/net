#ifndef PACKAGECOMMAND_H
#define PACKAGECOMMAND_H
#include <QObject>
#include "package/package.h"

class PackageCommand : public Package
{
    Q_OBJECT
public:
    explicit PackageCommand(QObject *parent=0 );
    explicit PackageCommand(quint16 _size, quint16 _com, QObject *parent=0);

    quint16 command;

    virtual QByteArray serialize();
    virtual quint16 getSize();

//    QDataStream& operator<<(QDataStream& out);

friend QDataStream & operator <<(QDataStream& s, const PackageCommand &us);
friend QDataStream & operator <<(QDataStream& s, const PackageCommand *us);
friend QDebug & operator <<(QDebug& s, const PackageCommand *us);

};


#endif // PACKAGECOMMAND_H
