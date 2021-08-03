#include "database.h"
#include <QList>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

DataBase::DataBase(QObject *parent) : QObject(parent)
{
     db=QSqlDatabase::addDatabase("QMYSQL");
}

bool DataBase::Connect(QString host,int port,QString db_name,QString user,QString pwd)
{
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(pwd);
    db.setDatabaseName(db_name);
    bool rt=db.open();
    sq=QSqlQuery(db);
    return rt;
}

bool DataBase::Exec(QString str)
{
    return sq.exec(str);
}

QList<int> DataBase::GetFriends(int uid)
{
    sq.exec("select friend_id from user_friends where user_id=" +QString::number(uid)+" union select user_id from user_friends where friend_id="+QString::number(uid)+";");
    QList<int>friends;
    while (sq.next())
    {
        /* code */
        friends.append(sq.value("friend_id").toInt());
    }
    return friends;
}
/*
select context from(select * from chat_record 
where (user_id=2 and rec_id=1) or (user_id=1 and rec_id=2)
order by send_time desc)temp group by send_time desc;
获取uid为1和2 的最新聊天记录
*/

void DataBase::AddFriend(int user,int friendd)
{
    sq.exec("insert into user_friends values("+user+QString(",")+friendd+")");
}

QList<chat> DataBase::GetChats(int uid1,int uid2,int type)
{
    QList<chat> chats;
    if(type==1)
        sq.exec(QString("select * from(select * from chat_record "
        "where (user_id=")+uid2+"and rec_id="+uid1+") or (user_id="+uid1+" and rec_id="+uid2+")"
        "order by send_time desc)temp group by send_time desc;");
    else sq.exec("select * from(select * from chat_record where rec_type=2 and rec_id="+uid2+QString(")or"));
    while(sq.next())
    {
        chat tp;
        tp.user_id=sq.value("user_id").toInt();
        tp.rec_id=sq.value("rec_id").toInt();
        tp.msg_type=sq.value("msg_type").toInt();
        tp.rec_type=sq.value("rec_type").toInt();
        tp.context=sq.value("context").toString();
        tp.send_time=sq.value("send_time").toInt();
        chats.append(tp);
    }
    return chats;
}

void DataBase::AddChat(chat ct)
{
    sq.exec("insert into chat_record value("+QString::number(ct.msg_type)+","+
    QString::number(ct.user_id)+","+
    QString::number(ct.rec_type)+","+
    QString::number(ct.rec_id)+","+
    "\'"+ct.context+"\'"+","+
    QString::number(ct.send_time)+QString(")"));
    // qDebug()<<"insert into chat_record value("+QString::number(ct.msg_type)+","+
    // QString::number(ct.user_id)+","+
    // QString::number(ct.rec_type)+","+
    // QString::number(ct.rec_id)+","+
    // "\'"+ct.context+","+"\'"+
    // QString::number(ct.send_time)+QString(")")<<endl;
    qDebug()<<"[DataBase]:AddChat."<<endl;
    qDebug()<<ct.send_time<<endl;
    qDebug()<<sq.lastError().text()<<endl;
    
}