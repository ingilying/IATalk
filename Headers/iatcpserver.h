#ifndef IATCPSERVER_H
#define IATCPSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QList>
#include "iatcpclient.h"

class IATcpServer : public QTcpServer
{
    Q_OBJECT
public:
    IATcpServer(QObject  *parent = nullptr , unsigned int port = 0);
    QList<IATcpClient*>clients_list;
protected:
    void incomingConnection(qintptr socketDescriptor);
protected slots:
    void NewMessage(QByteArray msg,int len);
    void ClientDisconnection(qintptr descriptor);
signals:
    void UpdateMessage(QByteArray msg,int len,IATcpClient* sender);
    void  Disconnect(IATcpClient* client);
    void NewConnection(IATcpClient* client);
};

#endif // IATCPSERVER_H
