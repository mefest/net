#include "mainwindow.h"
#include <QApplication>
#include <QTest>
#include <QThread>
#include "test/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTest::qExec(new test);


    return a.exec();
}
