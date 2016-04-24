#include "packagefilehandler.h"
#include <QFile>
#include <QDebug>

PackageFileHandler::PackageFileHandler(QObject *parent): Package(parent)
{
    CryptoHash=new QCryptographicHash(QCryptographicHash::Md5);
    partSize=2048;
    type=Package::FileHandler;
}

void PackageFileHandler::setPartSize(quint16 size)
{
    partCount=(fileSize+size-1)/size;
}

void PackageFileHandler::setPartCount(quint16 count)
{
    partSize=(fileSize+count-1)/count;
}

void PackageFileHandler::setFile(QFile &file)
{
    if(file.open(QFile::ReadOnly)){
        fileSize=file.size();
        setPartSize(partSize);
        fileName=file.fileName();
        CryptoHash->addData(&file);
        hash=CryptoHash->result();
    }
}

QByteArray PackageFileHandler::serialize()
{
    QByteArray block,buf;
    QDataStream out(&block, QIODevice::WriteOnly);
    buf = Package::serialize();
    out.writeRawData(buf.data(),buf.size());
    out<<fileName<<fileSize<<partCount<<partSize<<hash;
    return block;
}

quint16 PackageFileHandler::getSize()
{
    quint16 tmp=0;
    tmp+=Package::getSize();
    tmp+=sizeof(fileName);
    tmp+=sizeof(fileSize);
    tmp+=sizeof(partCount);
    tmp+=sizeof(partSize);
    tmp+=sizeof(hash.size());
    return tmp;
}

void PackageFileHandler::fromStream(QDataStream &stream)
{
    stream>>fileName>>fileSize>>partCount>>partSize>>hash;
}

void PackageFileHandler::dump()
{
    qDebug()<<"fileName\t"<<fileName<<"\t|";
    qDebug()<<"fileSize\t"<<fileSize<<"\t|";
    qDebug()<<"partCount\t"<<partCount<<"\t|";
    qDebug()<<"partSize\t"<<partSize<<"\t|";
    qDebug()<<"hash\t"<<hash<<"\t|";
}
