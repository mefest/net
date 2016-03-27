#ifndef PACKAGEMESSAGE_H
#define PACKAGEMESSAGE_H
#include <QObject>
#include "package/package.h"



class PackageMessage : public Package
{
    Q_OBJECT
public:
    explicit PackageMessage(QObject *parent=0 );
    explicit PackageMessage(quint16 _size, QString _mes, QObject *parent=0);

    void setMessage(QString mes);
    QString getMessage(){ return message;}


    virtual QByteArray serialize();
    virtual quint16 getSize();


    friend QDataStream & operator <<(QDataStream& s, const PackageMessage &us);
    friend QDataStream & operator <<(QDataStream& s, const PackageMessage *us);
private:
    QString message;



};

#endif // PACKAGEMESSAGE_H
