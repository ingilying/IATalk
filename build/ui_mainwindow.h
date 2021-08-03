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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QWidget *widget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *avatar;
    QLabel *user_name;
    QLabel *fri_avatar;
    QLabel *fri_name;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QListWidget *friends_list;
    QWidget *page_2;
    QTextEdit *textEdit;
    QPushButton *send_but;
    QListWidget *chat_list;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(852, 656);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 80, 120, 581));
        listWidget->setLayoutDirection(Qt::LeftToRight);
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget{\n"
"outline: 0px;\n"
"min-width: 120px;\n"
"max-width:120px;\n"
"color: Black;\n"
"background-color: rgb(246, 245, 244);\n"
"border:0px solid gray;\n"
"}\n"
"QListWidget::Item{\n"
"height:30px;\n"
"border:0px solid gray;\n"
"padding-left:15;\n"
"}\n"
"QListWidget::Item::selected{\n"
"color: rgb(0, 0, 0);\n"
"border-left: 10px solid Green \n"
"}"));
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setAlternatingRowColors(false);
        listWidget->setLayoutMode(QListView::SinglePass);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 851, 81));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        horizontalLayoutWidget = new QWidget(widget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 851, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        avatar = new QLabel(horizontalLayoutWidget);
        avatar->setObjectName(QString::fromUtf8("avatar"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(avatar->sizePolicy().hasHeightForWidth());
        avatar->setSizePolicy(sizePolicy);
        avatar->setMaximumSize(QSize(70, 70));
        avatar->setBaseSize(QSize(0, 0));

        horizontalLayout->addWidget(avatar);

        user_name = new QLabel(horizontalLayoutWidget);
        user_name->setObjectName(QString::fromUtf8("user_name"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(user_name->sizePolicy().hasHeightForWidth());
        user_name->setSizePolicy(sizePolicy1);
        user_name->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(user_name);

        fri_avatar = new QLabel(horizontalLayoutWidget);
        fri_avatar->setObjectName(QString::fromUtf8("fri_avatar"));
        fri_avatar->setMaximumSize(QSize(70, 70));

        horizontalLayout->addWidget(fri_avatar);

        fri_name = new QLabel(horizontalLayoutWidget);
        fri_name->setObjectName(QString::fromUtf8("fri_name"));

        horizontalLayout->addWidget(fri_name);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(120, 80, 121, 581));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        friends_list = new QListWidget(page);
        friends_list->setObjectName(QString::fromUtf8("friends_list"));
        friends_list->setGeometry(QRect(0, 0, 120, 581));
        friends_list->setStyleSheet(QString::fromUtf8("QListWidget{\n"
"outline: 0px;\n"
"min-width: 120px;\n"
"max-width:120px;\n"
"color: Black;\n"
"background-color: rgb(246, 245, 244);\n"
"border:0px solid gray;\n"
"}\n"
"QListWidget::Item{\n"
"height:30px;\n"
"border:0px solid gray;\n"
"padding-left:15;\n"
"}\n"
"QListWidget::Item::selected{\n"
"background: rgb(87, 227, 137);\n"
"color: Black;\n"
"}"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(240, 530, 611, 121));
        textEdit->setStyleSheet(QString::fromUtf8("color: Black;\n"
"background-color: rgb(246, 245, 244);"));
        textEdit->setFrameShape(QFrame::NoFrame);
        send_but = new QPushButton(centralwidget);
        send_but->setObjectName(QString::fromUtf8("send_but"));
        send_but->setEnabled(false);
        send_but->setGeometry(QRect(760, 620, 87, 26));
        send_but->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border: 0px;\n"
"	background: rgb(222, 221, 218);\n"
"	\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton::hover{\n"
"	border: 0px;\n"
"	background-color: rgb(154, 153, 150);\n"
"}\n"
"QPushButton::pressed{\n"
"	border: 1px rgb(222, 221, 218);\n"
"}"));
        send_but->setAutoDefault(false);
        chat_list = new QListWidget(centralwidget);
        chat_list->setObjectName(QString::fromUtf8("chat_list"));
        chat_list->setGeometry(QRect(240, 80, 611, 411));
        chat_list->setStyleSheet(QString::fromUtf8(""));
        chat_list->setFrameShape(QFrame::NoFrame);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        listWidget->setCurrentRow(-1);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IATalk", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "\345\245\275\345\217\213", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "\347\276\244\347\273\204", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        avatar->setText(QString());
        user_name->setText(QApplication::translate("MainWindow", "name", nullptr));
        fri_avatar->setText(QString());
        fri_name->setText(QString());
        send_but->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
