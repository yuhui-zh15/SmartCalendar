#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#define EXIT_CODE_REBOOT 233

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QFile languageFile(QString("language.ini"));
    languageFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ts(&languageFile);
    QString language = ts.readLine();
    QTranslator translator;
    translator.load(":/cn.qm");
    if (language == "1") {
        a.installTranslator(&translator);
    }
    LoginDialog lg;
    lg.show();
    int ret = a.exec();
    if (ret == EXIT_CODE_REBOOT) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
