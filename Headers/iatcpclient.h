#ifndef IATCPCLIENT_H
#define IATCPCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include "tools.h"

class IATcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    IATcpClient(QObject *parent=0);
    unsigned int index;
   // QString user;
    User user;
public slots:
    void  NewMessage();
    void  Disconnect();
signals:
    void UpdateMessage(QByteArray,int);
    void ClientDisconnect(qintptr );
};

#endif // IATCPCLIENT_H
