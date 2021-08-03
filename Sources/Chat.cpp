#include "Chat.h"

Chat::Chat(QObject *parent) : QObject(parent)
{

}

Chat::Chat(uint sender,uint recver,QString content)
{
    this->sender=sender;
    this->recver=recver;
    this->content=content;
}