#ifndef LOGINSETDIALOG_H
#define LOGINSETDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class LoginSetDialog;
}

class LoginSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginSetDialog(QWidget *parent = nullptr);
    ~LoginSetDialog();

private:
    Ui::LoginSetDialog *ui;
protected:
    void closeEvent(QCloseEvent *);
signals:
    void LSetClose(QString ip,int port);
private slots:
    void on_but_savesettings_clicked();
};

#endif // LOGINSETDIALOG_H
