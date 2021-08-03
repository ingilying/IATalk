/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLineEdit *edit_user;
    QLabel *label_2;
    QLineEdit *edit_pwd;
    QPushButton *pushButton;
    QPushButton *but_set;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 70, 67, 19));
        edit_user = new QLineEdit(LoginDialog);
        edit_user->setObjectName(QString::fromUtf8("edit_user"));
        edit_user->setGeometry(QRect(60, 90, 251, 21));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 120, 67, 19));
        edit_pwd = new QLineEdit(LoginDialog);
        edit_pwd->setObjectName(QString::fromUtf8("edit_pwd"));
        edit_pwd->setGeometry(QRect(60, 140, 251, 21));
        edit_pwd->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        edit_pwd->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 180, 131, 41));
        but_set = new QPushButton(LoginDialog);
        but_set->setObjectName(QString::fromUtf8("but_set"));
        but_set->setGeometry(QRect(300, 20, 87, 26));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "IATalk", nullptr));
        label->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215 \357\274\232", nullptr));
        label_2->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        edit_pwd->setText(QString());
        pushButton->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        but_set->setText(QApplication::translate("LoginDialog", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
