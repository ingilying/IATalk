/*
 主程序:主要负责调用IAServer类

*/
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QTextStream>
#include "iaserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream qin(stdin);
    QTextStream qout(stdout);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "iatalk_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }//以上是qt自动生成的代码
    IAServer server;
    server.Begin();//调用开始函数
    
    return a.exec();
}
