#include "iatcpserver.h"

IATcpServer::IATcpServer(QObject *parent,unsigned int port)
{
    listen(QHostAddress::Any,port);
}

void IATcpServer::incomingConnection(qintptr descriptor)
{
    IATcpClient *client=new IATcpClient(this);
    client->setSocketDescriptor(descriptor);
   // (clients_list.empty())if
    //    client->index=1;
    //else client->index=(*clients_list.end())->index+1;
    clients_list.append(client);
    connect(client,&IATcpClient::UpdateMessage,this,&IATcpServer::NewMessage);
    connect(client,&IATcpClient::ClientDisconnect,this,&IATcpServer::ClientDisconnection);
    emit NewConnection(client);
}


void IATcpServer::NewMessage(QByteArray str,int len)
{
    emit UpdateMessage(str,len,(IATcpClient*)sender());

}

void IATcpServer::ClientDisconnection(qintptr descriptor)
{
    IATcpClient *client;
   for(int i=0;i<clients_list.count();++i)
        if(clients_list.at(i)->socketDescriptor()==descriptor)
            {
                client=clients_list.at(i);
                clients_list.removeAt(i);
                emit Disconnect(client);
                return;
            }
}
