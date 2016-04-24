#include <QTest>
#include <QThread>
#include "test.h"
#include "server/server.h"
#include "client/client.h"
#include "package/packagemessage.h"
#include "package/packagecommand.h"
#include <QDebug>

test::test(QObject *parent) : QObject(parent)
{

}

void test::initTestCase()
{

}



void test::testSerialize()
{
    Package *cmd = new PackageCommand(this);
    PackageCommand *cmd2 = new PackageCommand(this);
    qobject_cast<PackageCommand*>(cmd)->command=quint16(17);
    QByteArray buf;
    QByteArray buf2;
    buf=cmd->serialize();
    buf2=buf;
    QDataStream out(&buf2, QIODevice::ReadWrite);
    out>>cmd2;
//    QBENCHMARK(cmd->serialize());
    QCOMPARE(quint16(cmd2->command),quint16(17));
    QCOMPARE(quint16(sizeof(cmd2->command)+4),cmd2->getSize());

    PackageMessage *msg = new PackageMessage(this);
    PackageMessage *msg2 = new PackageMessage(this);
    msg->setMessage("hi my server");
//    QBENCHMARK(msg->serialize());
    buf=msg->serialize();
    buf2=buf;
    out.device()->seek(0);

    out>>msg2;
    QCOMPARE(QString("hi my server"),msg->getMessage());
    QCOMPARE(msg2->getMessage(),msg->getMessage());
    QCOMPARE(quint16(sizeof(msg2->getMessage())+4),msg->getSize());

}
