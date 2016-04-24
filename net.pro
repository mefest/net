#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T23:13:06
#
#-------------------------------------------------

QT       += core gui network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = net
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server/server.cpp \
    client/client.cpp \
    server/managerclients.cpp \
    package/package.cpp \
    package/packagecommand.cpp \
    package/packagemessage.cpp \
    test/test.cpp \
    package/packageauth.cpp \
    server/authmanager.cpp \
    package/packagefilehandler.cpp

HEADERS  += mainwindow.h \
    server/server.h \
    client/client.h \
    server/managerclients.h \
    package/package.h \
    package/packagecommand.h \
    package/packagemessage.h \
    test/test.h \
    package/packageauth.h \
    server/authmanager.h \
    package/packagefilehandler.h

FORMS    += mainwindow.ui
