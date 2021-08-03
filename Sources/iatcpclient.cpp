#include "iatcpclient.h"


IATcpClient::IATcpClient(QObject *parent) : index(0)
{
    connect(this,&QTcpSocket::readyRead,this,&IATcpClient::NewMessage);
    connect(this,&QTcpSocket::disconnected,this,&IATcpClient::Disconnect);
}

void IATcpClient::NewMessage()
{
    QByteArray bytes=this->readAll();
    emit UpdateMessage(bytes,0);
}

void IATcpClient::Disconnect()
{
    emit ClientDisconnect(this->socketDescriptor());
}