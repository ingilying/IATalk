#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QTime>
#include <QObject>

class HttpDownload : public QObject
{
    Q_OBJECT

public:
    HttpDownload(QObject *parent = nullptr);
    ~HttpDownload();
    void StartDownload();
    void Clean();
    QString urls;
    QString dir;
    QString filen;
private:
    void createNetworkManager();
    void startRequest(QUrl url);
    bool is_head;
    int file_size;
private slots:
    void httpReadyRead();
    void httpFinished();
    void updateProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;
    QTime time;
signals:
    void Finished();
};

#endif // HTTPDOWNLOAD_H
