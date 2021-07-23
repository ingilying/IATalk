
#define IA_DEBUG
#ifdef IA_DEBUG
#include <QTextStream>
QTextStream qin(stdin),qout(stdout);
#endif //IA DEBUG

#include "datapackage.h"
#include <QBuffer>



DataPackage::DataPackage(QObject *parent):QObject(parent)
{
    type=TYPE_MESSAGE;
    len=0;
    data=nullptr;
}

void DataPackage::Init(qint8 tp,qint16 le,QByteArray  *arry)
{
    this->type=tp;
    this->len=le;
    this->data=arry;
    if((type!=0x01) && (type!=0x02))
        return;
}

void DataPackage::Init(QByteArray *bytes)
{
   QDataStream ds(bytes,QIODevice::ReadOnly);
   ds>>type>>len;
   char *datas=new char[1024];
   ds.readRawData(datas,len);
   data=new QByteArray(datas);
}

QByteArray DataPackage::ToByteArray()
{
    QByteArray raw;
    QDataStream stream(&raw,QIODevice::WriteOnly);
    stream<<type<<len;
    stream.writeRawData(*data,len);
    qout<<"[DataPck]:"<<*data<<endl;
    //std::cout<<raw.data()<<std::endl;
    qout<<"[DataPack]:"<<raw<<endl;
    return raw;
}