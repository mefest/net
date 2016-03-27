#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


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

    qDebug()<<"connect to localhost";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRecivPackage(Package *package)
{

}
