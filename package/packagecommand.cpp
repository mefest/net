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
    out.writeRawData(buf.data(),buf.size());
    out<<command;
    return block;
}

quint16 PackageCommand::getSize()
{
    quint16 tmp=0;
    tmp+=Package::getSize();
    tmp+=sizeof(command);
    return tmp;
}

void PackageCommand::fromStream(QDataStream &stream)
{
    stream>>command;
}

void PackageCommand::dump()
{
    qDebug()<<"command\t"<<command;
}


QDataStream &operator <<(QDataStream& s,const PackageCommand &us)
{
    return s << us.size<<us.type<<us.command;
}
QDataStream &operator <<(QDataStream& s,const PackageCommand *us)
{
    return s << us->size<<us->type<<us->command;
}


QDataStream &operator >>(QDataStream& s, PackageCommand *us)
{
    quint16 size;
    s>>size;
    quint16 type;
    s>>type;
    us->fromStream(s);
    return s;
}



