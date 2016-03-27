#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T23:13:06
#
#-------------------------------------------------

QT       += core gui network

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
    package/packagemessage.cpp

HEADERS  += mainwindow.h \
    server/server.h \
    client/client.h \
    server/managerclients.h \
    package/package.h \
    package/packagecommand.h \
    package/packagemessage.h

FORMS    += mainwindow.ui
