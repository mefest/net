#include "packagemessage.h"

#include <QDebug>

PackageMessage::PackageMessage(QObject *parent): Package(parent)
{
    type=Package::Message;
    size=getSize();
}

PackageMessage::PackageMessage(quint16 _size, QString _mes, QObject *parent):
    Package(_size,Package::Message,parent),message(_mes)
{
}

void PackageMessage::setMessage(QString mes)
{
    message=mes;
    size=getSize();
}

QByteArray PackageMessage::serialize()
{
    QByteArray block,buf;
    QDataStream out(&block, QIODevice::WriteOnly);
    buf = Package::serialize();
    qDebug()<<buf;
    out.writeRawData(buf.data(),buf.size());
    qDebug()<<block;
    out<<message;
//    qDebug()<<size<<type<<message;
    return block;
}

quint16 PackageMessage::getSize()
{
    quint16 tmp=0;
    tmp+=Package::getSize();
    tmp+=sizeof(message);
    return tmp;
}

QDataStream &operator <<(QDataStream& s,const PackageMessage &us)
{
    return s << us.size<<us.type<<us.message;
}
QDataStream &operator <<(QDataStream& s,const PackageMessage *us)
{
    return s << us->size<<us->type<<us->message;
}

