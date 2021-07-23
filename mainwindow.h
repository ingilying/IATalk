#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
class LoginDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTcpSocket* socket;
    LoginDialog* p;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void readData();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
