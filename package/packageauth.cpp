#include "packageauth.h"
#include <QDebug>

PackageAuth::PackageAuth(QObject *parent): Package(parent)
{
    type=Package::Auth;
}

void PackageAuth::fromStream(QDataStream &stream)
{
    stream>>login>>passwd;
}

QByteArray PackageAuth::serialize()
{
    QByteArray block,buf;
    QDataStream out(&block, QIODevice::WriteOnly);
    buf = Package::serialize();
    out.writeRawData(buf.data(),buf.size());
    out<<login<<passwd;
    return block;
}

quint16 PackageAuth::getSize()
{
    quint16 tmp=0;
    tmp+=Package::getSize();
    tmp+=sizeof(login);
    tmp+=sizeof(passwd);
    return tmp;
}

void PackageAuth::dump()
{
    qDebug()<<"LOGIN\t"<<login<<"\t|"<<"\nPASSWD\t"<<passwd<<"\t|";
}
