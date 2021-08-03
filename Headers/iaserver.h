/*
IAServer类：服务端主逻辑执行的类，
至于为什么在类里写而不在main函数里写，
是因为QObject可以连接槽函数
*/
#ifndef IASERVER_H
#define IASERVER_H

#include <QObject>
#include "iatcpserver.h"
#include "database.h"
#include <QTextStream>
#include <QTimer>
#include <QSettings>
#include "tools.h"



class IAServer : public QObject
{
    Q_OBJECT
public:
    explicit IAServer(QObject *parent = nullptr);
    void Begin();//开始函数，相当于main
    QTextStream qin,qout;//输入输出对象主要用来控制台输入输出
    IATcpServer* server;//TCP基础类定义
    unsigned int port;//端口
    QList<QTimer*>waits_list;//登录等待队列：
    //用户连接服务端之后要在规定的时间内发送登录数据，这个是计时器的队列，因为会有多个客户端
    QList<User>users;//在线用户列表
    DataBase sql_db;
    QSettings *settings;
    QList<chat*>chats;
    bool sql_ok;
private slots:
    void newConnect(IATcpClient* client);//新用户连接时的槽函数
    void newMessage(QByteArray msg,int len,IATcpClient* client);//客户端发送数据的槽函数
    void  clientDisconnect(IATcpClient* client);//客户端断连的槽函数
    void Timeout();//计时器超时的槽函数
};

#endif // IASERVER_H
