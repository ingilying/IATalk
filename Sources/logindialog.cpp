#include "logindialog.h"
#include "ui_logindialog.h"
#include "loginsetdialog.h"
#include "datapackage.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QFile>
#include <QApplication>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi((QDialog*)this);
    mainw=new MainWindow();
    //QFile server_cf(QApplication::applicationDirPath()+"/server.conf");
    //if(!server_cf.exists())
   // {
   //     server_cf.open(QIODevice::WriteOnly);
   // }
   // server_cf.close();
   // server_cf.deleteLater();
    QSettings settings_server("server.conf",QSettings::NativeFormat);
    ip=settings_server.value("ip").toString();
    port=settings_server.value("port").toInt();
    settings_server.deleteLater();
    // QFile file(QApplication::applicationDirPath()+"/user.conf");
    // if(!file.exists())
    // {
    //     file.open(QIODevice::ReadWrite);
    //     file.close();
    // }
    QSettings settings_user("user.conf",QSettings::NativeFormat);
    QString name=settings_user.value("user").toString();
    QString pwd=settings_user.value("pwd").toString();
    if(!(name.isNull() || pwd.isNull()))
    {
        this->ui->edit_user->setText(name);
        this->ui->edit_pwd->setText(QString(QByteArray::fromBase64(pwd.toUtf8())));
    }
    
}

LoginDialog::~LoginDialog()
{
    delete ui;
    delete setd;
   // delete settings_server;
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
    if(ui->edit_user->text()=="" || ui->edit_pwd->text()=="")
    {
        QMessageBox::information(this,"提示","用户和密码不能为空哦！",QMessageBox::Ok);
        return;
    }

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
    //QMessageBox::information(nullptr," ","连接成功",QMessageBox::Ok);
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
    //socket->waitForBytesWritten();
    


    QSettings settings_user("user.conf",QSettings::NativeFormat);
    settings_user.setValue("user",this->ui->edit_user->text());
    settings_user.setValue("pwd",QString(this->ui->edit_pwd->text().toUtf8().toBase64()));
    settings_user.deleteLater();
    QSettings server_cf("server.conf",QSettings::NativeFormat);
   server_cf.setValue("ip",ip);
   server_cf.setValue("port",port);
   server_cf.deleteLater();
    //mainw->show();
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
   
    this->socket->disconnectFromHost();
    socket->waitForDisconnected();
    event->accept();
}
