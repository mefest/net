#include "packagecommand.h"
#include <QDebug>

PackageCommand::PackageCommand(QObject *parent): Package(parent)
{
    size=getSize();
    command=0;
    type=Package::Command;
}

PackageCommand::PackageCommand(quint16 _size, quint16 _com, QObject *parent):
    Package(_size,Package::Command,parent),command(_com)
{
}

QByteArray PackageCommand::serialize()
{
    QByteArray block,buf;
    QDataStream out(&block, QIODevice::WriteOnly);
    buf = Package::serialize();
    qDebug()<<buf;
    out.writeRawData(buf.data(),buf.size());
    qDebug()<<block;
    out<<command;
    qDebug()<<size<<type<<command;
    return block;
}

quint16 PackageCommand::getSize()
{
    quint16 tmp=0;
    tmp+=Package::getSize();
    tmp+=sizeof(command);
    return tmp;
}

QDataStream &operator <<(QDataStream& s,const PackageCommand &us)
{
    return s << us.size<<us.type<<us.command;
}
QDataStream &operator <<(QDataStream& s,const PackageCommand *us)
{
    return s << us->size<<us->type<<us->command;
}

QDebug &operator <<(QDebug& s,const PackageCommand *us)
{
    return s << us->size<<us->type<<us->command;
}


