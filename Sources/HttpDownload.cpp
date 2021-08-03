#include "HttpDownload.h"
#include <QFileInfo>
#include <QDebug>
#include <QEventLoop>


HttpDownload::HttpDownload(QObject *parent)
    : QObject(parent),is_head(false),reply(nullptr)
{
    createNetworkManager();
}

HttpDownload::~HttpDownload()
{

}

void HttpDownload::createNetworkManager()
{
    manager = new QNetworkAccessManager(this);
}

void HttpDownload::startRequest(QUrl url)
{
    //get发送一个网络请求 返回网络应答
    reply = manager->get(QNetworkRequest(url));
    //每当有新的数据要读取时 发射信号
    connect(reply, &QNetworkReply::readyRead, this, &HttpDownload::httpReadyRead);
    //每当有下载进度更新时 发射信号 更新进度条和文本窗
    connect(reply, &QNetworkReply::downloadProgress, this, &HttpDownload::updateProgress);
    //应答处理结束时会发射finished信号
    connect(reply, &QNetworkReply::finished, this, &HttpDownload::httpFinished);
    //时间计时开始
    time.start();
}

void HttpDownload::StartDownload()
{
    url = urls;
//将URL路径存入QFileInfo类
    QFileInfo info(url.path());
//从info中得到文件名
    QString fileName(info.fileName());
//如果没有获取到info
    if(fileName.isEmpty()){
        qDebug()<<"[HttpDownload]:Download failed ,the file name is empty."<<endl;
        return;
    }
    else{
        QEventLoop event_loop;
        QNetworkReply *hrep = manager->head(QNetworkRequest(url));
        connect(hrep,&QNetworkReply::finished,&event_loop,&QEventLoop::quit);
        event_loop.exec(QEventLoop::ExcludeUserInputEvents);
        file_size=hrep->rawHeader(QString("Content-Length").toUtf8()).toInt();
        hrep->deleteLater();
        qDebug()<<"[HttpDownload:]"<<file_size<<endl;
        //建立文件
        filen=dir+"/"+fileName;
        file = new QFile(dir+"/"+fileName);
        qDebug()<<file->size()<<endl;
        if(file->size()==file_size)
        {
            Clean();
            return;
        }
        //如果文件没有打开的情况
        if(!file->open((QIODevice::WriteOnly))){
            delete file;
            file = nullptr;
            return;
        }

        //执行网络请求函数
        startRequest(url);
    }
}

void HttpDownload::Clean()
{
    if(reply!=nullptr)
        reply->deleteLater();
    reply = nullptr;
    if(file!=nullptr)
        file->close();
    file = nullptr;
    emit Finished();
}

void HttpDownload::httpReadyRead()
{
    if(file)
        file->write(reply->readAll());
}

void HttpDownload::httpFinished()
{
    qDebug()<<"Download finished"<<endl;
    if(file){
        file->close();
        delete file;
        file = nullptr;
    }
    reply->deleteLater();
    reply = nullptr;
    emit Finished();
}

void HttpDownload::updateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
   qDebug()<<"[HttpDownload]: "<<bytesReceived<<" of "<<bytesTotal<<endl;
}
