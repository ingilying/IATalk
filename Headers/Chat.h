#ifndef CHAT_H
#define CHAT_H
#include <QObject>

class Chat : public QObject{
    Q_OBJECT
public:
    Chat(QObject *parent=nullptr);
    Chat(uint sender,uint recver,QString content);
    QString content;
    uint sender;
    uint recver;
};

#endif