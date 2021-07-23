#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datapackage.h"
#include "logindialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
{
    if(socket==nullptr) return;
    DataPackage pak;
    QByteArray tmp=socket->readAll();
    pak.Init(&tmp);
    if(pak.type==0x13)
    {
        p->close();
        QMessageBox::information(nullptr,"温馨提示","登录成功啦!",QMessageBox::Ok);

    }
    QMessageBox::information(nullptr," ",tmp,QMessageBox::Ok);
}
