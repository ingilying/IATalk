#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginSetDialog;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
private:
    MainWindow* mainw=nullptr;
    LoginSetDialog* setd=nullptr;
    QTcpSocket* socket=nullptr;
    QString ip;
    int port;
private slots:
    void on_but_set_clicked();
    void lset_close(QString ip,int port);
    void on_pushButton_clicked();
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
