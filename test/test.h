#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "package/package.h"

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = 0);


    Package *pack;

signals:


private slots:
    void initTestCase();
    void testSerialize();

};

#endif // TEST_H
