#include "logindialog.h"
#include "ui_logindialog.h"
#include "loginsetdialog.h"
#include "datapackage.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi((QDialog*)this);
    mainw=new MainWindow();
}

LoginDialog::~LoginDialog()
{
    delete ui;
    delete setd;
}

void LoginDialog::on_but_set_clicked()
{
   // LoginSetDialog *sed = nullptr;
    if(setd==nullptr)
    {
        setd=new LoginSetDialog();
        connect(setd,&LoginSetDialog::LSetClose,this,&LoginDialog::lset_close);
    }
    if(setd!=nullptr)
        setd->show();
   // setd->exec();
}

void LoginDialog::lset_close(QString ip,int port)
{
    this->ip=ip;
    this->port=port;
}

void LoginDialog::on_pushButton_clicked()
{
    socket=new QTcpSocket();
    socket->abort();
    socket->connectToHost(ip,port);
    //QMessageBox::information(nullptr," ","ip:"+ip+"\n"+port,QMessageBox::Ok);
    if(!socket->waitForConnected(3000))
    {
        QMessageBox::information(nullptr,"温馨提示(真·温馨)","连接服务器失败，请检查一下网络是否连通。",
                                 QMessageBox::Ok);
        return;
    }
    QMessageBox::information(nullptr," ","连接成功",QMessageBox::Ok);
    connect(socket,&QTcpSocket::readyRead,mainw,&MainWindow::readData);
    DataPackage login_pack;
    QJsonObject jobj;
    jobj.insert("type","login");
    jobj.insert("user",ui->edit_user->text());
    jobj.insert("pwd",ui->edit_pwd->text());
    QJsonDocument jdoc;
    jdoc.setObject(jobj);
    QByteArray banry=jdoc.toJson(QJsonDocument::Compact);
    login_pack.Init(0x01,banry.size(),&banry);
    mainw->socket=socket;
    mainw->p=this;
    socket->write(login_pack.ToByteArray());
    mainw->show();
}
