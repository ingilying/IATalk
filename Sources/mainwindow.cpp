#define IA_DEBUG
#ifdef IA_DEBUG
#include <QTextStream>
QTextStream qinc(stdin),qoutc(stdout);
#endif //IA DEBUG
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "datapackage.h"
#include "logindialog.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <HttpDownload.h>
#include <QPixmap>
#include <QPainter>
#include <QJsonArray>
#include <QListWidget>
#include <QLabel>
#include <QFileInfo>
#include <QThread>
#include <QPushButton>
#include <QTextEdit>

#define IA_SAVE_DIR "http"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),friends(),chats(),select_user(nullptr)
{
    ui->setupUi(this);
    //net_manager=new QNetworkAccessManager();
    connect(this->ui->listWidget,&QListWidget::currentRowChanged,this->ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(this->ui->friends_list,&QListWidget::currentRowChanged,this,&MainWindow::Select);
    connect(this->ui->send_but,&QPushButton::clicked,this,&MainWindow::onSendButtonClicked);
    ui->listWidget->setCurrentRow(0);
    ui->friends_list->setCurrentRow(0);
    //this->setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
    socket->disconnectFromHost();
}

void MainWindow::readData()
{
    if(socket->bytesAvailable()<=0)
        return;
    if(socket==nullptr) return;
    DataPackage pak;
    QByteArray tmp=socket->readAll();
    buffer.append(tmp);
    int total_size=buffer.size();
    while(total_size)
    {
        if(total_size<(sizeof(qint8)+sizeof(qint16)))
            break;

        qoutc<<tmp<<endl;
        pak.Init(&buffer);
        qoutc<<"[MainWindow]:"<<pak.type<<endl;
        if(total_size<pak.len+(sizeof(qint8)+sizeof(qint16)))
            break;
        if(pak.type==0x13)
        {
            p->hide();
            this->show();
            //
            qoutc<<(*pak.data)<<endl;
            QByteArray bytes=*pak.data;
            QJsonDocument jdoc;
            QJsonParseError error;
            jdoc=QJsonDocument::fromJson(bytes,&error);
            qoutc<<error.errorString()<<endl;
            QJsonObject jobj=jdoc.object();
            user.fromJson(jobj);
            ui->avatar->setText(user.avatar);
            ui->user_name->setText(user.name);
            //ui->user_uid->setText(QString::number(user.index));
            downloader=new HttpDownload();
            downloader->urls=user.avatar;
            downloader->dir=QApplication::applicationDirPath()+"/"+IA_SAVE_DIR;
            connect(downloader,&HttpDownload::Finished,this,[this](){
                    qDebug()<<downloader->filen<<endl;
                    QPixmap bg=RadiusImage(downloader->filen,ui->avatar->size());
                    if(!bg.isNull())
                    {
                    ui->avatar->setPixmap(bg);
                    ui->avatar->setScaledContents(true);
                    }else{
                    ui->avatar->setPixmap(RadiusImage(":/Res/user.png",ui->avatar->size()));
                    ui->avatar->setScaledContents(true);
                    }
                //delete this->downloader;
            });
            downloader->StartDownload();
            {//请求好友列表  
            DataPackage *pack=new DataPackage();
            QJsonObject *poj=new QJsonObject();
            poj->insert("type","Get");
            poj->insert("context","friends_list");
            QJsonDocument *doc=new QJsonDocument();
            jdoc.setObject(*poj);
            bytes=jdoc.toJson(QJsonDocument::Compact);
            pack->Init(0x01,bytes.size(),&bytes);
            socket->write(pack->ToByteArray());
            socket->waitForBytesWritten();
            delete poj;
            poj=new QJsonObject();
            poj->insert("type","Get");
            poj->insert("context","chats");
            jdoc.setObject(*poj);
            bytes=jdoc.toJson(QJsonDocument::Compact);
            pack->Init(0x01,bytes.size(),&bytes);
            socket->write(pack->ToByteArray());
            socket->waitForBytesWritten();
            delete doc;
            delete poj;
            delete pack;
            }   
            //QMessageBox::information(nullptr,"温馨提示","登录成功啦!",QMessageBox::Ok);
        }else if(pak.type==0x14)
        {
            QMessageBox::information(nullptr,"超级温馨的提示！",
                                    "登录似乎有点错误，你检查一下用户密码有没有错！",QMessageBox::Ok);
        }else if(pak.type==0x01)
        {
            qoutc<<"[MainWindow]:A message comed."<<endl;
            QByteArray bytes=(*pak.data);
            QJsonDocument doc=QJsonDocument::fromJson(bytes);
            QJsonObject jobj=doc.object();
            QString type=jobj.value("type").toString();
            if(type=="friends_list")
            {
                qoutc<<"[MainWindow]:This is a friends list."<<endl;
                QJsonArray arypc=jobj.value("context") .toArray();
                for(QJsonValue i : arypc)
                {
                    qoutc<<"[MainWindow]:A friend."<<endl;
                    QJsonObject j=i.toObject();
                    User p;
                    p.fromJson(j);
                    friends.append(p);
                    //ui->layout_friend->addWidget(new QLabel(p.name));
                    QListWidgetItem *item=new QListWidgetItem();
                    item->setSizeHint(QSize(15,30));
                    item->setTextAlignment(Qt::AlignCenter);
                    item->setText(p.name);
                    ui->friends_list->addItem(item);
                }
            }else if (type=="msg")
            {
                uint m_sender=jobj.value("sender").toString().toInt();
                uint m_recver=jobj.value("recver").toString().toInt();
                QString content=jobj.value("content").toString();
                Chat *chat=new Chat(m_sender,m_recver,content);
                chats.append(chat);
                if(select_user)
                    UpdateMessage();
            }
        }
        tmp=buffer.right(total_size-pak.len-(sizeof(qint8)+sizeof(qint16)));
        total_size=tmp.size();
        buffer=tmp;
    }
        if(socket->bytesAvailable()>0)
            readData();
        //QMessageBox::information(nullptr," ",tmp,QMessageBox::Ok);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    p->close();
    //socket->disconnectFromHost();
   // delete socket;
    //delete p;
    event->accept();
    QApplication::exit();

}

QPixmap MainWindow::RadiusImage(QString fn,QSize sizec)
{
    QPixmap pixmap(fn);
    pixmap=pixmap.scaled(sizec,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    int width=sizec.width();
    int height=sizec.height();
    QPixmap image(width,height);
    image.fill(Qt::transparent);
    QPainterPath pp;
    pp.addEllipse(0,0,width,height);
    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setClipPath(pp);
    painter.drawPixmap(0,0,width,height,pixmap);
    return image;
}

void MainWindow::Select(int index)
{
    qoutc<<index<<endl;
    if(friends.isEmpty())
    {
        QThread::sleep(1000);
        qoutc<<"friends was empty."<<endl;
    }
    User select=friends.at(index);
    if(select_user!=nullptr)
        delete select_user;
    select_user=new User();
    select_user->avatar=select.avatar;
    select_user->index=select.index;
    select_user->name=select.name;
    qoutc<<select.name<<endl;
    qoutc<<select.avatar<<endl;
    this->ui->fri_name->setText(select.name);
   // this->ui->fri_avatar->setText(select.avatar);
       // downloader=new HttpDownload();
        if(downloader==nullptr)
            qoutc<<"dowloader is nullpter."<<endl;
        downloader->urls=select.avatar;
        //if(file_name==NULL)
          //  qoutc<<" file name is nullpter."<<endl;
        //downloader->setSaveDir(QApplication::applicationDirPath()+"/"+IA_SAVE_DIR);
        disconnect(downloader,&HttpDownload::Finished,0,0);
        connect(downloader,&HttpDownload::Finished,this,[this](){
                QPixmap bg=RadiusImage(downloader->filen,ui->fri_avatar->size());
                if(!bg.isNull())
                {
                    ui->fri_avatar->setPixmap(bg);
                    ui->fri_avatar->setScaledContents(true);
                }else{
                    ui->fri_avatar->setPixmap(RadiusImage(":/Res/user.png",ui->fri_avatar->size()));
                    ui->fri_avatar->setScaledContents(true);
            }
            //delete this->downloader;
        });
        //select_user=&select;
        downloader->StartDownload();
        ui->send_but->setEnabled(true);
        
        UpdateMessage();
        
}

void MainWindow::onSendButtonClicked()
{
    QString rstr=ui->textEdit->toPlainText();
    if(this->ui->chat_list==nullptr)
        qDebug()<<"45098"<<endl;
    if(select_user==NULL)
        qDebug()<<"45099"<<endl;
   // chats.insert(select_user->name,item->text());
    ui->chat_list->addItem("我:"+rstr);
    qoutc<<"select user:"<<select_user->index<<" "<<select_user->name<<endl;
    chats.append(new Chat(user.index,select_user->index,rstr));
    qoutc<<"counts of  take in :"<<chats.count()<<endl;
    ui->textEdit->setText("");
    DataPackage pack;
    QJsonDocument jdoc;
    QJsonObject jobj;
    jobj.insert("type","msg");
    jobj.insert("rtype","user");
    jobj.insert("recver",QString::number(select_user->index));
    jobj.insert("content",rstr);
    jdoc.setObject(jobj);
    QByteArray bytes=jdoc.toJson(QJsonDocument::Compact);
    pack.Init(0x01,bytes.size(),&bytes);
    socket->write(pack.ToByteArray());
}

void MainWindow::UpdateMessage()
{
    ui->chat_list->clear();
    qoutc<<"counts of take out :"<<chats.count()<<endl;
        for(int i=0;i<chats.count();++i)
        {
            qoutc<<"Sender:"<<chats[i]->sender<<endl;
            qoutc<<"Recver:"<<chats[i]->recver<<endl;
            qoutc<<"Select user :"<<select_user->index<<endl;
            qoutc<<"User:"<<user.index<<endl;
            if((chats[i]->sender == select_user->index) || (chats[i]->recver==select_user->index))
            {
                if(chats[i]->sender==user.index)
                    ui->chat_list->addItem("我:"+chats[i]->content);
                else ui->chat_list->addItem(User::getNameByID(chats[i]->sender,friends)+":"+chats[i]->content);
            }
        }
}