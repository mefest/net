#include "package/package.h"
#include <QDebug>

Package::Package(QObject *parent) : QObject(parent)
{
    size=0;
    type=Package::Unknow;
}

Package::Package(quint16 _size, Package::Package_Type _type, QObject *parent): size(_size),type(_type), QObject(parent)
{
}

QByteArray Package::serialize()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    size=getSize();
//    qDebug()<<size;
    out << size<<type;
    return block;
    }

quint16 Package::getSize()
{
    quint16 tmp=0;
//    qDebug()<<sizeof(size)<<sizeof(Package::Package_Type);
    tmp+=sizeof(size);
    tmp+=sizeof(type);
    return tmp;
}

