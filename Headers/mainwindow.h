#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QCloseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QList>
#include <QMap>
#include "Chat.h"
#include "../iatalk/Headers/tools.h"

class LoginDialog;
class HttpDownload;
class QListWidgetItem;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    User user,*select_user;
    QTcpSocket* socket;
    LoginDialog* p;
    HttpDownload* downloader;
    QList<User>friends;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void readData();
    void Select(int index);
    void onSendButtonClicked();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    QPixmap RadiusImage(QString fn,QSize sizec);
    //QList<QListWidgetItem*>chats;
    QList<Chat*> chats;
  //  QNetworkAccessManager* net_manager;
    void UpdateMessage();
    QByteArray buffer;
};
#endif // MAINWINDOW_H
