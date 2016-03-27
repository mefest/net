#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QByteArray>
#include <QDataStream>


class Package : public QObject
{
    Q_OBJECT
public:
    enum Package_Type : char
        {Unknow=0, Command, Message, FileHandler, FileBody, UserType=100};
    explicit Package(QObject *parent = 0);
    explicit Package(quint16 _size, Package_Type _type, QObject *parent = 0);

    quint16 size;
    Package_Type type;


    virtual QByteArray serialize();
    virtual quint16 getSize();


signals:

public slots:


};

#endif // PACKAGE_H
