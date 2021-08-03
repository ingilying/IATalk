/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *avatar;
    QLabel *user_name;
    QLabel *user_uid;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        avatar = new QLabel(centralwidget);
        avatar->setObjectName(QString::fromUtf8("avatar"));
        avatar->setGeometry(QRect(70, 60, 81, 81));
        avatar->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius: 50px;\n"
"}"));
        user_name = new QLabel(centralwidget);
        user_name->setObjectName(QString::fromUtf8("user_name"));
        user_name->setGeometry(QRect(70, 150, 67, 19));
        user_uid = new QLabel(centralwidget);
        user_uid->setObjectName(QString::fromUtf8("user_uid"));
        user_uid->setGeometry(QRect(70, 170, 67, 19));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        avatar->setText(QString());
        user_name->setText(QApplication::translate("MainWindow", "name", nullptr));
        user_uid->setText(QApplication::translate("MainWindow", "uid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
