#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>
#include <QVersionNumber>


class Package : public QObject
{
    Q_OBJECT
    Q_ENUMS(Package_Type)
public:
    enum Package_Type : quint16
        {Unknow=0, Command, Message,Auth, FileHandler, FileBody, UserType=100};
    explicit Package(QObject *parent = 0);
    explicit Package(quint16 _size, Package_Type _type, QObject *parent = 0);

    virtual QByteArray serialize();
    virtual quint16 getSize();
    virtual void fromStream(QDataStream &stream)=0;
    virtual void dump()=0;
    Package_Type getType() { return type; }
//    virtual void readRaw(QByteArray *buf)=0;

    const QVersionNumber version= QVersionNumber(0,0,1);

    qintptr user;

signals:

public slots:

protected:
    quint16 size;
    Package_Type type;

};

#endif // PACKAGE_H
