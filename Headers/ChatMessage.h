#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QObject>
#include <QWidget>

class ChatMessage : public QWidget{
        Q_OBJECT
public:
    explicit ChatMessage(QWidget *parent=nullptr);

};

#endif // !CHATMESSAGE_H