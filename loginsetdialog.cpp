#include "loginsetdialog.h"
#include "ui_loginsetdialog.h"
#include <QIntValidator>
#include <QMessageBox>

LoginSetDialog::LoginSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginSetDialog)
{
    ui->setupUi(this);
    ui->edit_port->setValidator(new QIntValidator(0,65525));
}

LoginSetDialog::~LoginSetDialog()
{
    delete ui;
}

void LoginSetDialog::closeEvent(QCloseEvent *event)
{
    emit LSetClose(ui->edit_ip->text(),ui->edit_port->text().toInt());
   // QMessageBox::information(nullptr," ",ui->edit_ip->text()+"\n"+ui->edit_port->text(),QMessageBox::Ok);
    event->accept();
}
