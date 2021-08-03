#include "iaserver.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QCoreApplication>
#include <QDateTime>
#include "datapackage.h"

IAServer::IAServer(QObject *parent) : QObject(parent) ,qin(stdin),qout(stdout),users(),waits_list()
{
    //初始化
    //用标准输入输出
}

void IAServer::Begin()
{
    settings=new QSettings( QCoreApplication::applicationDirPath()+QString("/configs/config.conf"),QSettings::NativeFormat);
   // qout<<"Prot: ";qout.flush();qout>>port;//输入端口
    port=settings->value("/server/port").toUInt();
    qout<<port<<endl;
    server=new IATcpServer(this,port);//初始化服务器
    connect(server,&IATcpServer::NewConnection,this,&IAServer::newConnect);//处理新连接
    connect(server,&IATcpServer::UpdateMessage,this,&IAServer::newMessage);//处理新数据
    connect(server,&IATcpServer::Disconnect,this,&IAServer::clientDisconnect);//处理客户端断链
    
    sql_ok=sql_db.Connect(settings->value("/sql/host").toString(),
    settings->value("/sql/port").toUInt(),
    settings->value("/sql/database").toString(),
    settings->value("/sql/user").toString(),
    settings->value("/sql/pwd").toString());
    if(sql_ok)
        qout<<"MySQL connected successfuled."<<endl;
    else    qout<<"MySQL connected failed."<<endl;
}

void IAServer::newConnect(IATcpClient* client)
{
    qout<<"A new client connected.\n"<<endl;
   // QTimer *timer=new QTimer(client);//新用户连接，等待用户的登录信息的计时器(将客户端设为父类是为了在后面超时时得到它)
  //  timer->setSingleShot(true);//设置只执行一次
  //  connect(timer,&QTimer::timeout,this,&IAServer::Timeout);//连接超时方法
//    connect(client,&IATcpClient::ClientDisconnect,this, [](){
//
//    })
    //waits_list.append(timer);//将计时器添加进等待队列
   // timer->start(3000);//计时器以3000秒开始计时
}

void IAServer::newMessage(QByteArray msg,int len,IATcpClient *client)
{
   // qout<<msg<<endl;
    DataPackage dp;
    dp.Init(&msg);
    qint8 type=dp.type;
    qint16 len_d=dp.len;
    QByteArray data=(*dp.data);
    if(type==0x01)//如果是信息
    {
        QJsonParseError error;
        QJsonDocument json_doc=QJsonDocument::fromJson(data,&error);
        qout<<error.errorString()<<endl;
        if(json_doc.isObject())
        {
            QJsonObject json_obj=json_doc.object();
            QString type_data=json_obj["type"].toString();
           
             if(type_data=="login")
            {
              //  qout<<"login ."<<endl;
                for(int i=0;i<waits_list.count();++i)
                {
                    //qout<<waits_list[i]<<endl;
                    if(waits_list[i]!=nullptr)
                        if(waits_list.at(i)->parent()==client)
                            {
                                waits_list.removeAt(i);
                                break;
                            }
                    else waits_list.removeAt(i);
                   // waits_list.removeAt(i);
                }
                QString user=json_obj["user"].toString();
                QString pwd=json_obj["pwd"].toString();
                if(!(user.isEmpty())&&!(pwd.isEmpty()))
                {
                    for (int i = 0; i < this->users.count(); ++i)
                    {
                        if(users[i].name==user)
                            return;
                    }
                    sql_db.Exec("select * from user where user='"+user+"'");
                    if(sql_db.sq.next())
                    {
                        QString real_pwd=sql_db.sq.value("pwd").toString();
                        int  login_times=sql_db.sq.value("login_times").toInt();
                        uint uid=sql_db.sq.value("uid").toInt();
                        if(login_times>=4)
                        {
                            int last_time=sql_db.sq.value("last_time").toInt();
                            if(!(QDateTime::currentDateTime().toTime_t()-last_time>=86400000))
                                return;
                        }
                        
                        if(real_pwd==pwd)
                        {
                            User userp;
                            userp.index=uid;
                            userp.name=user;
                            userp.avatar="http://localhost:8080/avatar/"+user+".jpg";
                            users.append(userp);
                            qout<<user<<" has logined successful."<<endl;
                            QJsonObject jo_user;
                            jo_user.insert("index",QString::number(uid));
                            jo_user.insert("name",user);
                            jo_user.insert("avatar",userp.avatar);
                            QJsonDocument jd_user;
                            jd_user.setObject(jo_user);
                            DataPackage dpcp;
                            QByteArray bytes_user=jd_user.toJson(QJsonDocument::Compact);
                            dpcp.Init(0x13,bytes_user.size(),&bytes_user);
                            client->user=userp;
                            client->write(dpcp.ToByteArray());
                            client->waitForBytesWritten();
                            sql_db.Exec("update user set login_times="+QString::number(1)+" where uid="+QString::number(userp.index));
                           // client->write("sssssssssssssssss");
                            client->waitForBytesWritten();
                            return;
                        }else sql_db.Exec("update user set login_times="+QString::number(1+login_times)+" where uid="+QString::number(uid));
                    }
                }
                DataPackage pack_error;
                QByteArray error=QString("failed").toUtf8();
                pack_error.Init(0x14,error.size(),&error);
                client->write(pack_error.ToByteArray());
                client->waitForBytesWritten(5000);
                //client->disconnectFromHost();
            }else if(type_data=="msg")
            {
                qout<<"[Message]A message comed."<<endl;
                QString rtype=json_obj["rtype"].toString();
                int id=json_obj["recver"].toString().toInt();
                QString content=json_obj["content"].toString();
                if(rtype=="user")
                {
                    qout<<"[Message]one to one."<<endl;
                    chat *ct=new chat;
                    ct->context=content;
                    ct->msg_type=0x01;
                    ct->rec_id=id;
                    ct->rec_type=0x01;
                    ct->user_id=client->user.index;
                    qout<<"[Message]:Recver index is "<<id<<endl;
                    ct->send_time=QDateTime::currentDateTime().toTime_t();
                    this->sql_db.Exec("select user from user where uid="+QString::number(id));
                    if(sql_db.sq.next())
                    {
                        qout<<"[Message]:"<<client->user.name<<" to "<<sql_db.sq.value("user").toString()<<" : "<<content<<endl;
                        for(User i : users)
                        {
                            if(i.index==id)
                            {
                                for(IATcpClient* c : server->clients_list)
                                {
                                    if(c->user.index==id)
                                    {
                                        DataPackage pack;
                                        QJsonDocument jdoc;
                                        QJsonObject jobj;
                                        jobj.insert("type","msg");
                                        jobj.insert("sender",QString::number(client->user.index));
                                        jobj.insert("content",content);
                                        jdoc.setObject(jobj);
                                        QByteArray bytes=jdoc.toJson(QJsonDocument::Compact);
                                        pack.Init(0x01,bytes.size(),&bytes);
                                        c->write(pack.ToByteArray());
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        //chats.append(ct);
                        this->sql_db.AddChat(*ct);
                        delete ct;
                    }
                    
                }
            }else if (type_data=="Get")
            {
                qout<<"[Main]:A Get message comed."<<endl;
                QString context=json_obj.value("context").toString();
                if(context=="friends_list")
                {
                    qout<<"[Main]:This is a Get message of friends list"<<endl;
                    QJsonDocument jdoc;
                    QJsonObject joj;
                    QJsonArray jay;
                    auto ary=this->sql_db.GetFriends(client->user.index);
                    for(auto i : ary)
                    {
                        
                        this->sql_db.Exec("select * from user where uid="+QString::number(i));
                        if(sql_db.sq.next())
                        {
                            User tp;
                            tp.index=sql_db.sq.value("uid").toInt();
                            tp.name=sql_db.sq.value("user").toString();
                            tp.avatar="http://localhost:8080/avatar/"+tp.name+".jpg";
                            jay.append(tp.toJson());
                        }
                    }
                    joj.insert("type","friends_list");
                    joj.insert("context",jay);
                    jdoc.setObject(joj);
                    DataPackage pak;
                    QByteArray bytes=jdoc.toJson(QJsonDocument::Compact);
                    pak.Init(0x01,bytes.size(),&bytes);
                    qout<<"[Main]:"<<pak.ToByteArray()<<endl;
                    qout<<client->write(pak.ToByteArray())<<endl;
                    client->waitForBytesWritten(5000);
                   // client->disconnectFromHost();
                    qout<<"[Main]:Message writen."<<endl;
                }else if (context=="chats")
                {
                    QJsonObject joj;
                    QJsonDocument jdoc;
                    QByteArray bytes;
                    DataPackage pack;
                    auto ary=sql_db.GetFriends(client->user.index);
                    for(int id : ary)
                    {
                        auto ay=sql_db.GetChats(client->user.index,id,1);
                        for(int i=ay.count()-1;i>=0;--i)
                        {
                            joj=ay[i].toJson();
                            jdoc.setObject(joj);
                            bytes=jdoc.toJson(QJsonDocument::Compact);
                            pack.Init(0x01,bytes.size(),&bytes);
                            client->write(pack.ToByteArray());
                            client->waitForBytesWritten();
                            
                        }
                    }
                }
            }
        }
         
    }else if(type==0x20)//如果是文件
    {

    }else {//数据包错误
        // Dat
        // client->write();
    }
    if(client->bytesAvailable()>0)
        client->NewMessage();
}
void IAServer::Timeout()
{//超时就将客户端断连
    IATcpClient *client=(IATcpClient*)this->sender()->parent();//获取客户端
    client->disconnect();//将客户端的连接断开
    client->close();//关闭接口
    for(int i=0;i<server->clients_list.count();++i)
        if(client->socketDescriptor()==server->clients_list.at(i)->socketDescriptor())//寻找client
        {
            server->clients_list.removeAt(i);//找到就删除
            for(int i=0;i<waits_list.count();++i)
                    if (waits_list.at(i)->parent()==client)
                    {
                        waits_list.removeAt(i);//把相关的计时器也删除
                        return;
                    }
            return;
        }
}

void IAServer::clientDisconnect(IATcpClient* client)
{
    qout<<"A client dissconnected just now."<<endl;
    for(int i=0;i<users.count();++i)
    {
        if(users.at(i).index==client->user.index)
        {
            qout<<users.at(i).name<<" offed line."<<endl;
            users.removeAt(i);//用户断链，删除相关数据
            return;
        }
    }
}
