#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include "package/packagemessage.h"
#include "package/packageauth.h"
#include "package/packagefilehandler.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Server *serv= new Server(this);
    if(serv->start(QHostAddress::Any,1024)){
        qDebug()<<"run server";
    }
    Client *client = new Client(this);
    client->connectTo("localhost",1024);
    PackageAuth *pkAuth= new PackageAuth();
    pkAuth->login="mefest";
    client->sendPackage(pkAuth);

    PackageFileHandler *fl= new PackageFileHandler();
    QFile file("Makefile");
    fl->setFile(file);
    qDebug()<<fl->hash;

    client->sendPackage(fl);

    PackageMessage *pkMes= new PackageMessage();
    pkMes->setMessage("hi my favorite server");
    client->sendPackage(pkMes);
    qDebug()<<"connect to localhost";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRecivPackage(Package *package)
{

}
