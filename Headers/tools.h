#ifndef TOOLS_H
#define TOOLS_H

#include <QJsonObject>
#include <QJsonValue>

struct User
{
    /* data */
    uint index;
    QString name;
    QString avatar;
    void fromJson(QJsonObject oj)
    {
        index=oj.value("index").toString().toInt();
        name=oj.value("name").toString();
        avatar=oj.value("avatar").toString();
    };
    QJsonObject toJson()
    {
        QJsonObject obj;
        obj.insert("index",QString::number(index));
        obj.insert("name",name);
        obj.insert("avatar",avatar);
        return obj;
    };
    static QString getNameByID(uint id,QList<User> users)
    {
        for(User i : users)
        {
            if(i.index==id)
            {
                return i.name;
            }
        }
        return QString("");
    }
};


#endif