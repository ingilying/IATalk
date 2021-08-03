/********************************************************************************
** Form generated from reading UI file 'loginsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSETDIALOG_H
#define UI_LOGINSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginSetDialog
{
public:
    QLabel *label;
    QLineEdit *edit_ip;
    QLabel *label_2;
    QLineEdit *edit_port;
    QPushButton *but_savesettings;

    void setupUi(QDialog *LoginSetDialog)
    {
        if (LoginSetDialog->objectName().isEmpty())
            LoginSetDialog->setObjectName(QString::fromUtf8("LoginSetDialog"));
        LoginSetDialog->resize(400, 300);
        label = new QLabel(LoginSetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 67, 19));
        edit_ip = new QLineEdit(LoginSetDialog);
        edit_ip->setObjectName(QString::fromUtf8("edit_ip"));
        edit_ip->setGeometry(QRect(100, 50, 211, 21));
        edit_ip->setEchoMode(QLineEdit::Normal);
        label_2 = new QLabel(LoginSetDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 51, 19));
        edit_port = new QLineEdit(LoginSetDialog);
        edit_port->setObjectName(QString::fromUtf8("edit_port"));
        edit_port->setGeometry(QRect(100, 80, 211, 21));
        edit_port->setEchoMode(QLineEdit::Normal);
        but_savesettings = new QPushButton(LoginSetDialog);
        but_savesettings->setObjectName(QString::fromUtf8("but_savesettings"));
        but_savesettings->setGeometry(QRect(280, 230, 101, 41));

        retranslateUi(LoginSetDialog);

        QMetaObject::connectSlotsByName(LoginSetDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginSetDialog)
    {
        LoginSetDialog->setWindowTitle(QApplication::translate("LoginSetDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("LoginSetDialog", "\346\234\215\345\212\241\345\231\250:", nullptr));
        label_2->setText(QApplication::translate("LoginSetDialog", "\347\253\257\345\217\243\357\274\232", nullptr));
        but_savesettings->setText(QApplication::translate("LoginSetDialog", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginSetDialog: public Ui_LoginSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSETDIALOG_H
