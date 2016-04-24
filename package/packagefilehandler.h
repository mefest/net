#ifndef PACKAGEFILEHANDLER_H
#define PACKAGEFILEHANDLER_H

#include <QObject>
#include <QCryptographicHash>
#include <QFile>

#include "package/package.h"

class PackageFileHandler : public Package
{
public:
    explicit PackageFileHandler(QObject *parent=0);

    QCryptographicHash *CryptoHash;
    QByteArray hash;
    QString fileName;
    quint64 fileSize;

    quint16 getPartSize() {return partSize;}
    quint16 getPartCount() {return partCount;}
    void setPartSize(quint16 size);
    void setPartCount(quint16 count);
    void setFile(QFile &file);
private:
    quint16 partSize;
    quint16 partCount;

    // Package interface
public:
    QByteArray serialize();
    quint16 getSize();
    void fromStream(QDataStream &stream);
    void dump();
};

#endif // PACKAGEFILEHANDLER_H
