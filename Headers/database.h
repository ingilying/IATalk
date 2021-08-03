#ifndef  DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QJsonObject>
#include <QJsonValue>

struct chat{
    int user_id,rec_id;
    int msg_type,rec_type;
    QString context;
    int send_time;
    QJsonObject toJson()
    {
        QJsonObject jobj;
        jobj.insert("type","msg");
        jobj.insert("rtype","user");
        jobj.insert("sender",QString::number(user_id));
        jobj.insert("recver",QString::number(rec_id));
        jobj.insert("content",context);
        return jobj;
    }
};

class DataBase: public QObject{
    Q_OBJECT
public:
    QSqlDatabase db;
    QSqlQuery sq;
    DataBase(QObject *parent=nullptr);
    bool Connect(QString host,int port,QString db_name,QString user,QString pwd);
    bool  Exec(QString str);
    QList<int> GetFriends(int uid);
    void AddFriend(int user,int friendd);
    QList<chat> GetChats(int uid1,int uid2,int type);
    void AddChat(chat ct);
    //void AddChats(QList<chat>ct);
};

#endif // ! DATABASE_H