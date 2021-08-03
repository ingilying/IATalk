#ifndef DATAPACKAGE_H
#define DATAPACKAGE_H

#include <QObject>
#include <QDataStream>
#include <QtNetwork/QTcpSocket>

#define TYPE_MESSAGE 0x01;
#define TYPE_FILE 0x02;

class DataPackage : public QObject{

public:
        qint8 type;
        qint16 len;
        QByteArray *data;
        DataPackage(QObject *parent=nullptr);
        void Init(qint8 tp,qint16 le,QByteArray *arry);
        void Init(QByteArray *bytes);
        QByteArray ToByteArray();
};


#endif  //DataPackage_h

